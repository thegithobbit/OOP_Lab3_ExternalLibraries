# Retrospective: Using External Library in C++ Project

## General Information

This laboratory work is based on a previous object-oriented programming project about transport classes. The original project already had an inheritance hierarchy for different transport types and several queue implementations.

For this laboratory work, the project was extended with an external C++ library: `nlohmann/json`.

## What Tasks Were Planned for the Library?

The main task for the external library was to add persistent data storage to the program.

The library was planned to solve the following tasks:

- convert C++ transport objects into JSON format;
- save a collection of transport objects to a JSON file;
- load transport objects from a JSON file;
- restore the correct derived class based on the `"type"` field;
- make saved data readable and editable outside the program.

## Why Was This Library Chosen?

The `nlohmann/json` library was chosen because it is one of the most popular JSON libraries for C++. It has a simple syntax and works naturally with modern C++ code.

Compared with some other JSON libraries, `nlohmann/json` is easier to start using because JSON values can be created with initializer lists and accessed in a readable way.

Another reason for choosing this library is that it is header-only and can be easily integrated into a CMake project using `FetchContent`.

## Installation and Configuration Experience

The library was connected through CMake using `FetchContent`.

This approach was convenient because it did not require manually downloading files into the repository. During the first CMake configuration, the library is downloaded automatically from GitHub.

The configuration was mostly simple. One small warning appeared about `DOWNLOAD_EXTRACT_TIMESTAMP`, and it was fixed by adding this option to `FetchContent_Declare`.

## Documentation Experience

The official documentation and GitHub repository were useful. The examples clearly show how to create JSON objects, read fields, write JSON to files, and format output.

The most useful resources were:

- Official GitHub repository: https://github.com/nlohmann/json
- Integration examples with CMake: https://json.nlohmann.me/integration/cmake/
- Basic usage examples: https://json.nlohmann.me/

The documentation was enough for the tasks in this project.

## How the Library Was Used in Code

The library is used in two main files:

- `TransportClasses.h`
- `main.cpp`

In `TransportClasses.h`, every transport class has a `toJson()` method. This method converts the object into a JSON object.

There is also a `transportFromJson()` function. It reads the `"type"` field from JSON and creates the correct C++ object, for example `Car`, `Bus`, `Plane`, `Truck`, or another transport type.

In `main.cpp`, the library is used in:

- `saveTransportsToJson()`
- `loadTransportsFromJson()`

The save function creates a JSON array and writes it to a file. The load function reads JSON from a file and restores transport objects.

## Convenience of Use

The library was convenient to use. Creating JSON objects from C++ data was simple and readable.

For example, code like this is clear:

```cpp
data["enginePower"] = enginePower;
```

Also, formatting output with indentation was easy:

```cpp
output << data.dump(4);
```

This made the generated JSON file readable for a human.

## Behavior and Interaction with Own Code
The behavior of the library was understandable. JSON fields can be accessed with at() when the field is required, and with value() when a default value is acceptable.

The interaction between the library and the object-oriented class hierarchy was also logical. Each class is responsible for converting itself to JSON, while the factory function transportFromJson() is responsible for creating objects from JSON.

## Problems During Work
One small issue was related to CMake. During configuration, CMake showed a warning about DOWNLOAD_EXTRACT_TIMESTAMP. This was solved by adding:

```
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
```

Another challenge was that the program has polymorphic objects stored as shared_ptr<Transport>. Because of this, loading from JSON required a separate factory function that checks the "type" field and creates the correct derived class.

This problem was solved with the transportFromJson() function.