#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Queue.h"
#include "TransportClasses.h"

using namespace std;
using json = nlohmann::json;

void ignoreLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt) {
    int val;

    while (true) {
        cout << prompt;

        if (cin >> val) {
            break;
        }

        cout << "Invalid input! Please enter a number.\n";
        ignoreLine();
    }

    ignoreLine();
    return val;
}

double readDouble(const string& prompt) {
    double val;

    while (true) {
        cout << prompt;

        if (cin >> val) {
            break;
        }

        cout << "Invalid input! Please enter a number.\n";
        ignoreLine();
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

void rebuildQueues(
    const vector<shared_ptr<Transport>>& transports,
    LinkedListQueue& linkedQueue,
    HeapQueue& heapQueue,
    AVLQueue& avlQueue
) {
    linkedQueue = LinkedListQueue();
    heapQueue = HeapQueue();
    avlQueue = AVLQueue();

    for (const auto& transport : transports) {
        linkedQueue.insert(transport);
        heapQueue.insert(transport);
        avlQueue.insert(transport);
    }
}

void saveTransportsToJson(const vector<shared_ptr<Transport>>& transports, const string& fileName) {
    json data = json::array();

    for (const auto& transport : transports) {
        data.push_back(transport->toJson());
    }

    ofstream output(fileName);

    if (!output) {
        cout << "Could not open file for writing: " << fileName << endl;
        return;
    }

    output << data.dump(4);
    cout << "Saved " << transports.size() << " transports to " << fileName << endl;
}

vector<shared_ptr<Transport>> loadTransportsFromJson(const string& fileName) {
    ifstream input(fileName);

    if (!input) {
        cout << "Could not open file for reading: " << fileName << endl;
        return {};
    }

    try {
        json data;
        input >> data;

        vector<shared_ptr<Transport>> transports;

        for (const auto& item : data) {
            auto transport = transportFromJson(item);

            if (transport) {
                transports.push_back(transport);
            }
        }

        cout << "Loaded " << transports.size() << " transports from " << fileName << endl;
        return transports;
    } catch (const exception& error) {
        cout << "Failed to load JSON file: " << error.what() << endl;
        return {};
    }
}

shared_ptr<Transport> createTransport() {
    string type = readString("\nSelect transport type (Car, Bus, Plane, Boat, Truck, Bicycle, Train): ");
    string name = readString("Name: ");
    int number = readInt("Number: ");
    double speed = readDouble("Speed: ");
    double weight = readDouble("Weight: ");

    string fuel;
    int passengers;
    int carriages;
    double enginePower;
    double routeLength;
    double wingspan;
    double maxAltitude;
    double length;
    double draft;
    double cargoCapacity;

    if (type == "Car") {
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        enginePower = readDouble("Engine power: ");
        return make_shared<Car>(name, number, fuel, speed, weight, passengers, enginePower);
    }

    if (type == "Bus") {
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        routeLength = readDouble("Route length: ");
        return make_shared<Bus>(name, number, fuel, speed, weight, passengers, routeLength);
    }

    if (type == "Plane") {
        fuel = readString("Fuel: ");
        wingspan = readDouble("Wingspan: ");
        maxAltitude = readDouble("Max altitude: ");
        return make_shared<Plane>(name, number, fuel, speed, weight, wingspan, maxAltitude);
    }

    if (type == "Boat") {
        fuel = readString("Fuel: ");
        length = readDouble("Length: ");
        draft = readDouble("Draft: ");
        return make_shared<Boat>(name, number, fuel, speed, weight, length, draft);
    }

    if (type == "Truck") {
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        cargoCapacity = readDouble("Cargo capacity: ");
        return make_shared<Truck>(name, number, fuel, speed, weight, passengers, cargoCapacity);
    }

    if (type == "Bicycle") {
        return make_shared<Bicycle>(name, number, speed, weight);
    }

    if (type == "Train") {
        fuel = readString("Fuel: ");
        passengers = readInt("Passengers: ");
        carriages = readInt("Carriages: ");
        return make_shared<Train>(name, number, fuel, speed, weight, passengers, carriages);
    }

    cout << "Unknown transport type.\n";
    return nullptr;
}

void showMethods(shared_ptr<Transport> transport) {
    cout << "\nAvailable actions:\n";
    cout << "1 - printInfo\n2 - calculateRange\n3 - honk\n";

    if (dynamic_pointer_cast<Car>(transport)) {
        cout << "4 - turboBoost\n5 - drift\n";
    } else if (dynamic_pointer_cast<Bus>(transport)) {
        cout << "4 - openDoors\n5 - announceRoute\n";
    } else if (dynamic_pointer_cast<Plane>(transport)) {
        cout << "4 - takeOff\n5 - land\n";
    } else if (dynamic_pointer_cast<Boat>(transport)) {
        cout << "4 - dock\n5 - sail\n";
    } else if (dynamic_pointer_cast<Truck>(transport)) {
        cout << "4 - loadCargo\n5 - unloadCargo\n";
    } else if (dynamic_pointer_cast<Bicycle>(transport)) {
        cout << "4 - pedal\n5 - ringBell\n";
    } else if (dynamic_pointer_cast<Train>(transport)) {
        cout << "4 - depart\n5 - stop\n";
    }
}

void executeMethod(shared_ptr<Transport> transport, int choice) {
    switch (choice) {
        case 1:
            transport->printInfo();
            break;
        case 2:
            cout << transport->calculateRange() << endl;
            break;
        case 3:
            transport->honk();
            break;
        default:
            break;
    }

    if (auto car = dynamic_pointer_cast<Car>(transport)) {
        if (choice == 4) car->turboBoost();
        if (choice == 5) car->drift();
    } else if (auto bus = dynamic_pointer_cast<Bus>(transport)) {
        if (choice == 4) bus->openDoors();
        if (choice == 5) bus->announceRoute();
    } else if (auto plane = dynamic_pointer_cast<Plane>(transport)) {
        if (choice == 4) plane->takeOff();
        if (choice == 5) plane->land();
    } else if (auto boat = dynamic_pointer_cast<Boat>(transport)) {
        if (choice == 4) boat->dock();
        if (choice == 5) boat->sail();
    } else if (auto truck = dynamic_pointer_cast<Truck>(transport)) {
        if (choice == 4) truck->loadCargo();
        if (choice == 5) truck->unloadCargo();
    } else if (auto bicycle = dynamic_pointer_cast<Bicycle>(transport)) {
        if (choice == 4) bicycle->pedal();
        if (choice == 5) bicycle->ringBell();
    } else if (auto train = dynamic_pointer_cast<Train>(transport)) {
        if (choice == 4) train->depart();
        if (choice == 5) train->stop();
    }
}

int main() {
    vector<shared_ptr<Transport>> transports;
    LinkedListQueue linkedQueue;
    HeapQueue heapQueue;
    AVLQueue avlQueue;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1 - Add transport\n";
        cout << "2 - Show all transports\n";
        cout << "3 - Show queues\n";
        cout << "4 - Play with transport\n";
        cout << "5 - Save transports to JSON\n";
        cout << "6 - Load transports from JSON\n";
        cout << "0 - Exit\n";

        int choice = readInt("Choice: ");

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            auto transport = createTransport();

            if (transport) {
                transports.push_back(transport);
                linkedQueue.insert(transport);
                heapQueue.insert(transport);
                avlQueue.insert(transport);
            }
        } else if (choice == 2) {
            if (transports.empty()) {
                cout << "No transports available.\n";
            }

            for (size_t i = 0; i < transports.size(); ++i) {
                cout << "\nIndex: " << i << endl;
                transports[i]->printInfo();
            }
        } else if (choice == 3) {
            cout << "\nLinkedList Queue:\n";
            linkedQueue.printQueue();

            cout << "\nHeap Queue:\n";
            heapQueue.printQueue();

            cout << "\nAVL Queue:\n";
            avlQueue.printQueue();
        } else if (choice == 4) {
            if (transports.empty()) {
                cout << "No transports available.\n";
                continue;
            }

            int index = readInt("Select Transport by index (0 to " + to_string(transports.size() - 1) + "): ");

            if (index >= 0 && index < static_cast<int>(transports.size())) {
                while (true) {
                    showMethods(transports[index]);
                    int action = readInt("Select action (0 to exit): ");

                    if (action == 0) {
                        break;
                    }

                    executeMethod(transports[index], action);
                }
            } else {
                cout << "Invalid index.\n";
            }
        } else if (choice == 5) {
            string fileName = readString("File name to save (example: transports.json): ");
            saveTransportsToJson(transports, fileName);
        } else if (choice == 6) {
            string fileName = readString("File name to load (example: transports.json): ");
            transports = loadTransportsFromJson(fileName);
            rebuildQueues(transports, linkedQueue, heapQueue, avlQueue);
        } else {
            cout << "Unknown menu option.\n";
        }
    }

    return 0;
}