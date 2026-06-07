cmake_minimum_required(VERSION 3.20)

project(OOP_Lab3_ExternalLibraries LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(transport_manager
        main.cpp
)

target_link_libraries(transport_manager PRIVATE nlohmann_json::nlohmann_json)