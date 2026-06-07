#ifndef QUEUE_H
#define QUEUE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "TransportClasses.h"

using namespace std;

class LinkedListQueue {
private:
    struct Node {
        shared_ptr<Transport> data;
        Node* next;

        explicit Node(shared_ptr<Transport> transport)
            : data(transport), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    LinkedListQueue() : head(nullptr), tail(nullptr) {}

    LinkedListQueue(const LinkedListQueue&) = delete;
    LinkedListQueue& operator=(const LinkedListQueue&) = delete;

    LinkedListQueue(LinkedListQueue&& other) noexcept
        : head(other.head), tail(other.tail) {
        other.head = nullptr;
        other.tail = nullptr;
    }

    LinkedListQueue& operator=(LinkedListQueue&& other) noexcept {
        if (this != &other) {
            clear();

            head = other.head;
            tail = other.tail;

            other.head = nullptr;
            other.tail = nullptr;
        }

        return *this;
    }

    ~LinkedListQueue() {
        clear();
    }

    void clear() {
        while (head) {
            Node* current = head;
            head = head->next;
            delete current;
        }

        tail = nullptr;
    }

    void insert(shared_ptr<Transport> transport) {
        Node* node = new Node(transport);

        if (!tail) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    shared_ptr<Transport> pop() {
        if (!head) {
            return nullptr;
        }

        Node* current = head;
        shared_ptr<Transport> result = head->data;

        head = head->next;

        if (!head) {
            tail = nullptr;
        }

        delete current;
        return result;
    }

    bool empty() const {
        return head == nullptr;
    }

    void printQueue() const {
        Node* current = head;

        while (current) {
            current->data->printInfo();
            current = current->next;
        }
    }
};

class HeapQueue {
private:
    vector<shared_ptr<Transport>> heap;

    void heapifyUp(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;

            if (heap[index]->getPriority() <= heap[parent]->getPriority()) {
                break;
            }

            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void heapifyDown(size_t index) {
        while (true) {
            size_t left = index * 2 + 1;
            size_t right = index * 2 + 2;
            size_t largest = index;

            if (left < heap.size() && heap[left]->getPriority() > heap[largest]->getPriority()) {
                largest = left;
            }

            if (right < heap.size() && heap[right]->getPriority() > heap[largest]->getPriority()) {
                largest = right;
            }

            if (largest == index) {
                break;
            }

            swap(heap[index], heap[largest]);
            index = largest;
        }
    }

public:
    void clear() {
        heap.clear();
    }

    void insert(shared_ptr<Transport> transport) {
        heap.push_back(transport);
        heapifyUp(heap.size() - 1);
    }

    shared_ptr<Transport> pop() {
        if (heap.empty()) {
            return nullptr;
        }

        shared_ptr<Transport> result = heap.front();

        heap.front() = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            heapifyDown(0);
        }

        return result;
    }

    bool empty() const {
        return heap.empty();
    }

    void printQueue() const {
        for (const auto& transport : heap) {
            transport->printInfo();
        }
    }
};

class AVLQueue {
private:
    struct Node {
        shared_ptr<Transport> data;
        Node* left;
        Node* right;
        int height;

        explicit Node(shared_ptr<Transport> transport)
            : data(transport), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balanceNode(Node* node) {
        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) < 0) {
                node->left = leftRotate(node->left);
            }

            return rightRotate(node);
        }

        if (balance < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rightRotate(node->right);
            }

            return leftRotate(node);
        }

        return node;
    }

    Node* insertNode(Node* node, shared_ptr<Transport> transport) {
        if (!node) {
            return new Node(transport);
        }

        if (transport->getPriority() < node->data->getPriority()) {
            node->left = insertNode(node->left, transport);
        } else {
            node->right = insertNode(node->right, transport);
        }

        return balanceNode(node);
    }

    Node* removeMax(Node* node, shared_ptr<Transport>& removed) {
        if (!node) {
            return nullptr;
        }

        if (!node->right) {
            removed = node->data;
            Node* leftSubtree = node->left;
            delete node;
            return leftSubtree;
        }

        node->right = removeMax(node->right, removed);
        return balanceNode(node);
    }

    void printInOrder(Node* node) const {
        if (!node) {
            return;
        }

        printInOrder(node->left);
        node->data->printInfo();
        printInOrder(node->right);
    }

    void deleteTree(Node* node) {
        if (!node) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    AVLQueue() : root(nullptr) {}

    AVLQueue(const AVLQueue&) = delete;
    AVLQueue& operator=(const AVLQueue&) = delete;

    AVLQueue(AVLQueue&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    AVLQueue& operator=(AVLQueue&& other) noexcept {
        if (this != &other) {
            clear();

            root = other.root;
            other.root = nullptr;
        }

        return *this;
    }

    ~AVLQueue() {
        clear();
    }

    void clear() {
        deleteTree(root);
        root = nullptr;
    }

    void insert(shared_ptr<Transport> transport) {
        root = insertNode(root, transport);
    }

    shared_ptr<Transport> pop() {
        shared_ptr<Transport> removed = nullptr;
        root = removeMax(root, removed);
        return removed;
    }

    bool empty() const {
        return root == nullptr;
    }

    void printQueue() const {
        printInOrder(root);
    }
};

#endif