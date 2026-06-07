#ifndef TRANSPORTCLASSES_H
#define TRANSPORTCLASSES_H

#include <iostream>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Transport {
protected:
    string type;
    string name;
    int number;
    string fuel;
    double speed;
    double weight;

    json baseJson() const {
        return {
            {"type", type},
            {"name", name},
            {"number", number},
            {"fuel", fuel},
            {"speed", speed},
            {"weight", weight}
        };
    }

public:
    Transport(string t, string n, int num, string f, double s, double w)
        : type(t), name(n), number(num), fuel(f), speed(s), weight(w) {}

    virtual void printInfo() {
        cout << "Type: " << type << ", Name: " << name << ", Number: " << number
             << ", Fuel: " << fuel << ", Speed: " << speed << ", Weight: " << weight << endl;
    }

    virtual json toJson() const {
        return baseJson();
    }

    string getType() const {
        return type;
    }

    string getName() const {
        return name;
    }

    virtual double calculateRange() {
        return speed * 10;
    }

    virtual int getPriority() {
        return static_cast<int>(speed);
    }

    virtual void honk() {
        cout << name << " honks!\n";
    }

    virtual ~Transport() {}
};

class LandTransport : public Transport {
protected:
    int wheels;
    int passengers;

public:
    LandTransport(string t, string n, int num, string f, double s, double w, int wh, int p)
        : Transport(t, n, num, f, s, w), wheels(wh), passengers(p) {}

    void printInfo() override {
        Transport::printInfo();
        cout << "Wheels: " << wheels << ", Passengers: " << passengers << endl;
    }

    json toJson() const override {
        json data = baseJson();
        data["wheels"] = wheels;
        data["passengers"] = passengers;
        return data;
    }

    void move() {
        cout << name << " is moving on the road.\n";
    }
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

    json toJson() const override {
        json data = LandTransport::toJson();
        data["enginePower"] = enginePower;
        return data;
    }

    void turboBoost() {
        speed *= 1.2;
        cout << name << " activated turbo! Speed: " << speed << endl;
    }

    void drift() {
        cout << name << " is drifting!\n";
    }

    int getPriority() override {
        return static_cast<int>(speed + enginePower / 10);
    }
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

    json toJson() const override {
        json data = LandTransport::toJson();
        data["routeLength"] = routeLength;
        return data;
    }

    void openDoors() {
        cout << name << " doors opened.\n";
    }

    void announceRoute() {
        cout << name << " announces its route.\n";
    }

    int getPriority() override {
        return passengers;
    }
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

    json toJson() const override {
        json data = baseJson();
        data["wingspan"] = wingspan;
        data["maxAltitude"] = maxAltitude;
        return data;
    }

    void takeOff() {
        cout << name << " is taking off!\n";
    }

    void land() {
        cout << name << " is landing!\n";
    }

    int getPriority() override {
        return static_cast<int>(speed + maxAltitude / 1000);
    }
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

    json toJson() const override {
        json data = baseJson();
        data["length"] = length;
        data["draft"] = draft;
        return data;
    }

    void dock() {
        cout << name << " is docking.\n";
    }

    void sail() {
        cout << name << " is sailing.\n";
    }

    int getPriority() override {
        return static_cast<int>(speed + length / 10);
    }
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

    json toJson() const override {
        json data = LandTransport::toJson();
        data["cargoCapacity"] = cargoCapacity;
        return data;
    }

    void loadCargo() {
        cout << name << " loading cargo.\n";
    }

    void unloadCargo() {
        cout << name << " unloading cargo.\n";
    }

    int getPriority() override {
        return static_cast<int>(cargoCapacity + speed / 2);
    }
};

class Bicycle : public LandTransport {
public:
    Bicycle(string n, int num, double s, double w)
        : LandTransport("Bicycle", n, num, "none", s, w, 2, 1) {}

    void pedal() {
        cout << name << " is pedaling.\n";
    }

    void ringBell() {
        cout << name << " rings the bell!\n";
    }

    int getPriority() override {
        return static_cast<int>(speed);
    }
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

    json toJson() const override {
        json data = LandTransport::toJson();
        data["carriages"] = carriages;
        return data;
    }

    void depart() {
        cout << name << " is departing.\n";
    }

    void stop() {
        cout << name << " stopped.\n";
    }

    int getPriority() override {
        return passengers + carriages;
    }
};

inline shared_ptr<Transport> transportFromJson(const json& data) {
    const string type = data.at("type").get<string>();
    const string name = data.at("name").get<string>();
    const int number = data.at("number").get<int>();
    const string fuel = data.value("fuel", "none");
    const double speed = data.at("speed").get<double>();
    const double weight = data.at("weight").get<double>();

    if (type == "Car") {
        return make_shared<Car>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("passengers").get<int>(),
            data.at("enginePower").get<double>()
        );
    }

    if (type == "Bus") {
        return make_shared<Bus>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("passengers").get<int>(),
            data.at("routeLength").get<double>()
        );
    }

    if (type == "Plane") {
        return make_shared<Plane>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("wingspan").get<double>(),
            data.at("maxAltitude").get<double>()
        );
    }

    if (type == "Boat") {
        return make_shared<Boat>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("length").get<double>(),
            data.at("draft").get<double>()
        );
    }

    if (type == "Truck") {
        return make_shared<Truck>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("passengers").get<int>(),
            data.at("cargoCapacity").get<double>()
        );
    }

    if (type == "Bicycle") {
        return make_shared<Bicycle>(name, number, speed, weight);
    }

    if (type == "Train") {
        return make_shared<Train>(
            name,
            number,
            fuel,
            speed,
            weight,
            data.at("passengers").get<int>(),
            data.at("carriages").get<int>()
        );
    }

    return nullptr;
}

#endif