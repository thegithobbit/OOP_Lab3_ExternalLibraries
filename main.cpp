#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include "TransportClasses.h"
#include "Queue.h"
using namespace std;

void ignoreLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int val;
    while(true) {
        cout << prompt;
        if(cin >> val) break;
        else {
            cout << "Invalid input! Please enter a number.\n";
            ignoreLine();
        }
    }
    ignoreLine();
    return val;
}

double readDouble(const string& prompt) {
    double val;
    while(true) {
        cout << prompt;
        if(cin >> val) break;
        else {
            cout << "Invalid input! Please enter a number.\n";
            ignoreLine();
        }
    }
    ignoreLine();
    return val;
}

string readString(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

shared_ptr<Transport> createTransport() {
    string type = readString("\nSelect transport type (Car, Bus, Plane, Boat, Truck, Bicycle, Train): ");
    string name = readString("Name: ");
    int number = readInt("Number: ");
    double speed = readDouble("Speed: ");
    double weight = readDouble("Weight: ");

    string fuel;
    int passengers, carriages;
    double enginePower, routeLength, wingspan, maxAltitude, length, draft, cargoCapacity;

    if(type == "Car"){
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        enginePower = readDouble("Engine power: ");
        return make_shared<Car>(name, number, fuel, speed, weight, passengers, enginePower);
    } else if(type == "Bus"){
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        routeLength = readDouble("Route length: ");
        return make_shared<Bus>(name, number, fuel, speed, weight, passengers, routeLength);
    } else if(type == "Plane"){
        fuel = readString("Fuel: ");
        wingspan = readDouble("Wingspan: ");
        maxAltitude = readDouble("Max altitude: ");
        return make_shared<Plane>(name, number, fuel, speed, weight, wingspan, maxAltitude);
    } else if(type == "Boat"){
        fuel = readString("Fuel: ");
        length = readDouble("Length: ");
        draft = readDouble("Draft: ");
        return make_shared<Boat>(name, number, fuel, speed, weight, length, draft);
    } else if(type == "Truck"){
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        cargoCapacity = readDouble("Cargo capacity: ");
        return make_shared<Truck>(name, number, fuel, speed, weight, passengers, cargoCapacity);
    } else if(type == "Bicycle"){
        return make_shared<Bicycle>(name, number, speed, weight);
    } else if(type == "Train"){
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        carriages = readInt("Carriages: ");
        return make_shared<Train>(name, number, fuel, speed, weight, passengers, carriages);
    } else {
        cout << "Unknown transport type.\n";
        return nullptr;
    }
}

void showMethods(shared_ptr<Transport> t) {
    cout << "\nAvailable actions:\n";
    cout << "1 - printInfo\n2 - calculateRange\n3 - honk\n";
    if (dynamic_pointer_cast<Car>(t)) cout << "4 - turboBoost\n5 - drift\n";
    else if (dynamic_pointer_cast<Bus>(t)) cout << "4 - openDoors\n5 - announceRoute\n";
    else if (dynamic_pointer_cast<Plane>(t)) cout << "4 - takeOff\n5 - land\n";
    else if (dynamic_pointer_cast<Boat>(t)) cout << "4 - dock\n5 - sail\n";
    else if (dynamic_pointer_cast<Truck>(t)) cout << "4 - loadCargo\n5 - unloadCargo\n";
    else if (dynamic_pointer_cast<Bicycle>(t)) cout << "4 - pedal\n5 - ringBell\n";
    else if (dynamic_pointer_cast<Train>(t)) cout << "4 - depart\n5 - stop\n";
}

void executeMethod(shared_ptr<Transport> t, int choice) {
    switch(choice) {
        case 1: t->printInfo(); break;
        case 2: cout << t->calculateRange() << endl; break;
        case 3: t->honk(); break;
    }
    if (auto car = dynamic_pointer_cast<Car>(t)) {
        if(choice == 4) car->turboBoost();
        if(choice == 5) car->drift();
    } else if (auto bus = dynamic_pointer_cast<Bus>(t)) {
        if(choice == 4) bus->openDoors();
        if(choice == 5) bus->announceRoute();
    } else if (auto plane = dynamic_pointer_cast<Plane>(t)) {
        if(choice == 4) plane->takeOff();
        if(choice == 5) plane->land();
    } else if (auto boat = dynamic_pointer_cast<Boat>(t)) {
        if(choice == 4) boat->dock();
        if(choice == 5) boat->sail();
    } else if (auto truck = dynamic_pointer_cast<Truck>(t)) {
        if(choice == 4) truck->loadCargo();
        if(choice == 5) truck->unloadCargo();
    } else if (auto bicycle = dynamic_pointer_cast<Bicycle>(t)) {
        if(choice == 4) bicycle->pedal();
        if(choice == 5) bicycle->ringBell();
    } else if (auto train = dynamic_pointer_cast<Train>(t)) {
        if(choice == 4) train->depart();
        if(choice == 5) train->stop();
    }
}

int main() {
    vector<shared_ptr<Transport>> transports;
    LinkedListQueue linkedQueue;
    HeapQueue heapQueue;
    AVLQueue avlQueue;

    int n = readInt("Enter number of transports: ");
    for(int i = 0; i < n; i++) {
        auto t = createTransport();
        if(t) {
            transports.push_back(t);
            linkedQueue.insert(t);
            heapQueue.insert(t);
            avlQueue.insert(t);
        } else i--;
    }

    while(true){
        cout << "\nMenu:\n1 - Show all transports\n2 - Show queues\n3 - Play with transport\n0 - Exit\nChoice: ";
        int choice = readInt("");
        if(choice == 0) break;
        else if(choice == 1){
            for(auto& t : transports) t->printInfo();
        } else if(choice == 2){
            cout << "\nLinkedList Queue:\n"; linkedQueue.printQueue();
            cout << "\nHeap Queue:\n"; heapQueue.printQueue();
            cout << "\nAVL Queue:\n"; avlQueue.printQueue();
        } else if(choice == 3){
            int idx = readInt("Select Transport by index (0 to " + to_string(transports.size()-1) + "): ");
            if(idx >=0 && idx < transports.size()){
                while(true){
                    showMethods(transports[idx]);
                    int action = readInt("Select action (0 to exit): ");
                    if(action == 0) break;
                    executeMethod(transports[idx], action);
                }
            } else cout << "Invalid index.\n";
        }
    }
    return 0;
}