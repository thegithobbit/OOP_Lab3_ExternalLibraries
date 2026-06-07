# OOP Lab 3: Transport Manager with External Library

## Project Description

This project is a C++ console application for managing different types of transport. It is based on a previous object-oriented programming laboratory work about transport classes and queues.

The program supports creating, displaying, saving, and loading transport objects. The project demonstrates object-oriented programming concepts such as inheritance, polymorphism, virtual methods, and dynamic casting.

## External Library

The project uses the external C++ library:

- [nlohmann/json](https://github.com/nlohmann/json)

This library is not part of the C++ standard library. It is used to work with JSON data.

## How the Library Is Used

The `nlohmann/json` library is used for:

- converting transport objects to JSON;
- saving a list of transport objects to a `.json` file;
- loading transport objects from a `.json` file;
- reading JSON fields and creating the correct C++ transport class based on the `"type"` field;
- formatting JSON output with indentation using `dump(4)`.

Main places where the library is used:

- `TransportClasses.h`
    - `toJson()` methods;
    - `transportFromJson()` function;
- `main.cpp`
    - `saveTransportsToJson()` function;
    - `loadTransportsFromJson()` function.

## Transport Types

The program supports the following transport types:

- Car
- Bus
- Plane
- Boat
- Truck
- Bicycle
- Train

Each transport type has common fields, such as name, number, speed, weight, and fuel. Some transport types also have additional fields, for example engine power, route length, wingspan, cargo capacity, or number of carriages.

## Program Features

The console menu allows the user to:

1. Add a new transport object.
2. Show all transport objects.
3. Show transport queues.
4. Execute actions for a selected transport object.
5. Save all transport objects to a JSON file.
6. Load transport objects from a JSON file.
7. Exit the program.

## Sample JSON Data

A sample file is provided:

```text
data/sample_transports.json