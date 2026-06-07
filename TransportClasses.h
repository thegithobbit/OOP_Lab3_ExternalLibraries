#ifndef TRANSPORTCLASSES_H
#define TRANSPORTCLASSES_H

#include <iostream>
#include <string>
using namespace std;

class Transport {
protected:
    string type;
    string name;
    int number;
    string fuel;
    double speed;
    double weight;

public:
    Transport(string t, string n, int num, string f, double s, double w)
        : type(t), name(n), number(num), fuel(f), speed(s), weight(w) {}

    virtual void printInfo() {
        cout << "Type: " << type << ", Name: " << name << ", Number: " << number
             << ", Fuel: " << fuel << ", Speed: " << speed << ", Weight: " << weight << endl;
    }

    virtual double calculateRange() { return speed * 10; }
    virtual int getPriority() { return static_cast<int>(speed); }
    virtual void honk() { cout << name << " honks!\n"; }
    virtual ~Transport() {}
};

class LandTransport : public Transport {
protected:
    int wheels;
    int passengers;

public:
    LandTransport(string t, string n, int num, string f, double s, double w, int wh, int p)
        : Transport(t,n,num,f,s,w), wheels(wh), passengers(p) {}

    void printInfo() override {
        Transport::printInfo();
        cout << "Wheels: " << wheels << ", Passengers: " << passengers << endl;
    }

    void move() { cout << name << " is moving on the road.\n"; }
};

class Car : public LandTransport {
    double enginePower;
public:
    Car(string n, int num, string f, double s, double w, int p, double ep)
        : LandTransport("Car", n, num, f, s, w, 4, p), enginePower(ep) {}

    void printInfo() override {
        LandTransport::printInfo();
        cout << "Engine Power: " << enginePower << " HP\n";
    }

    void turboBoost() { speed *= 1.2; cout << name << " activated turbo! Speed: " << speed << endl; }
    void drift() { cout << name << " is drifting!\n"; }

    int getPriority() override { return static_cast<int>(speed + enginePower/10); }
};

class Bus : public LandTransport {
    double routeLength;
public:
    Bus(string n, int num, string f, double s, double w, int p, double rl)
        : LandTransport("Bus", n, num, f, s, w, 6, p), routeLength(rl) {}

    void printInfo() override {
        LandTransport::printInfo();
        cout << "Route Length: " << routeLength << " km\n";
    }

    void openDoors() { cout << name << " doors opened.\n"; }
    void announceRoute() { cout << name << " announces its route.\n"; }

    int getPriority() override { return passengers; }
};

class Plane : public Transport {
    double wingspan;
    double maxAltitude;
public:
    Plane(string n, int num, string f, double s, double w, double ws, double ma)
        : Transport("Plane", n, num, f, s, w), wingspan(ws), maxAltitude(ma) {}

    void printInfo() override {
        Transport::printInfo();
        cout << "Wingspan: " << wingspan << ", Max Altitude: " << maxAltitude << endl;
    }

    void takeOff() { cout << name << " is taking off!\n"; }
    void land() { cout << name << " is landing!\n"; }

    int getPriority() override { return static_cast<int>(speed + maxAltitude/1000); }
};

class Boat : public Transport {
    double length;
    double draft;
public:
    Boat(string n, int num, string f, double s, double w, double l, double d)
        : Transport("Boat", n, num, f, s, w), length(l), draft(d) {}

    void printInfo() override {
        Transport::printInfo();
        cout << "Length: " << length << ", Draft: " << draft << endl;
    }

    void dock() { cout << name << " is docking.\n"; }
    void sail() { cout << name << " is sailing.\n"; }

    int getPriority() override { return static_cast<int>(speed + length/10); }
};

class Truck : public LandTransport {
    double cargoCapacity;
public:
    Truck(string n, int num, string f, double s, double w, int p, double cc)
        : LandTransport("Truck", n, num, f, s, w, 6, p), cargoCapacity(cc) {}

    void printInfo() override {
        LandTransport::printInfo();
        cout << "Cargo Capacity: " << cargoCapacity << " tons\n";
    }

    void loadCargo() { cout << name << " loading cargo.\n"; }
    void unloadCargo() { cout << name << " unloading cargo.\n"; }

    int getPriority() override { return static_cast<int>(cargoCapacity + speed/2); }
};

class Bicycle : public LandTransport {
public:
    Bicycle(string n, int num, double s, double w)
        : LandTransport("Bicycle", n, num, "none", s, w, 2, 1) {}

    void pedal() { cout << name << " is pedaling.\n"; }
    void ringBell() { cout << name << " rings the bell!\n"; }

    int getPriority() override { return static_cast<int>(speed); }
};

class Train : public LandTransport {
    int carriages;
public:
    Train(string n, int num, string f, double s, double w, int p, int c)
        : LandTransport("Train", n, num, f, s, w, 8, p), carriages(c) {}

    void printInfo() override {
        LandTransport::printInfo();
        cout << "Carriages: " << carriages << endl;
    }

    void depart() { cout << name << " is departing.\n"; }
    void stop() { cout << name << " stopped.\n"; }

    int getPriority() override { return passengers + carriages; }
};

#endif