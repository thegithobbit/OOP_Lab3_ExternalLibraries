#ifndef QUEUE_H
#define QUEUE_H

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
        Node(shared_ptr<Transport> t) : data(t), next(nullptr) {}
    };
    Node* head;
    Node* tail;
public:
    LinkedListQueue() : head(nullptr), tail(nullptr) {}
    ~LinkedListQueue() {
        while(head) { Node* tmp=head; head=head->next; delete tmp; }
    }

    void insert(shared_ptr<Transport> t) {
        Node* node = new Node(t);
        if(!tail) head=tail=node;
        else { tail->next=node; tail=node; }
    }

    shared_ptr<Transport> pop() {
        if(!head) return nullptr;
        Node* tmp=head;
        shared_ptr<Transport> ret=head->data;
        head=head->next;
        if(!head) tail=nullptr;
        delete tmp;
        return ret;
    }

    bool empty() { return head==nullptr; }

    void printQueue() {
        Node* curr=head;
        while(curr) { curr->data->printInfo(); curr=curr->next; }
    }
};

class HeapQueue {
private:
    vector<shared_ptr<Transport>> heap;

    void heapifyUp(int index) {
        while(index>0){
            int parent=(index-1)/2;
            if(heap[index]->getPriority()<=heap[parent]->getPriority()) break;
            swap(heap[index], heap[parent]);
            index=parent;
        }
    }
    void heapifyDown(int index) {
        int left=index*2+1, right=index*2+2, largest=index;
        if(left<heap.size() && heap[left]->getPriority()>heap[largest]->getPriority()) largest=left;
        if(right<heap.size() && heap[right]->getPriority()>heap[largest]->getPriority()) largest=right;
        if(largest!=index) { swap(heap[index], heap[largest]); heapifyDown(largest); }
    }

public:
    void insert(shared_ptr<Transport> t) {
        heap.push_back(t);
        heapifyUp(heap.size()-1);
    }

    shared_ptr<Transport> pop() {
        if(heap.empty()) return nullptr;
        shared_ptr<Transport> ret=heap[0];
        heap[0]=heap.back(); heap.pop_back();
        heapifyDown(0);
        return ret;
    }

    bool empty() { return heap.empty(); }

    void printQueue() {
        for(auto& t: heap) t->printInfo();
    }
};

class AVLQueue {
    struct Node {
        shared_ptr<Transport> data;
        Node* left;
        Node* right;
        int height;
        Node(shared_ptr<Transport> t): data(t), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;

    int getHeight(Node* n) { return n? n->height : 0; }
    int getBalance(Node* n) { return n? getHeight(n->left)-getHeight(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x=y->left; Node* T2=x->right;
        x->right=y; y->left=T2;
        y->height=max(getHeight(y->left), getHeight(y->right))+1;
        x->height=max(getHeight(x->left), getHeight(x->right))+1;
        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y=x->right; Node* T2=y->left;
        y->left=x; x->right=T2;
        x->height=max(getHeight(x->left), getHeight(x->right))+1;
        y->height=max(getHeight(y->left), getHeight(y->right))+1;
        return y;
    }

    Node* insertNode(Node* node, shared_ptr<Transport> t) {
        if(!node) return new Node(t);
        if(t->getPriority()<node->data->getPriority()) node->left=insertNode(node->left,t);
        else node->right=insertNode(node->right,t);

        node->height=1+max(getHeight(node->left), getHeight(node->right));
        int balance=getBalance(node);

        if(balance>1 && t->getPriority()<node->left->data->getPriority()) return rightRotate(node);
        if(balance<-1 && t->getPriority()>=node->right->data->getPriority()) return leftRotate(node);
        if(balance>1 && t->getPriority()>=node->left->data->getPriority()){
            node->left=leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance<-1 && t->getPriority()<node->right->data->getPriority()){
            node->right=rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node* node){
        if(!node) return;
        inorder(node->left);
        node->data->printInfo();
        inorder(node->right);
    }

public:
    AVLQueue(): root(nullptr) {}
    void insert(shared_ptr<Transport> t){ root=insertNode(root,t); }
    shared_ptr<Transport> pop(){ return nullptr; }
    bool empty(){ return root==nullptr; }
    void printQueue(){ inorder(root); }
};

#endif