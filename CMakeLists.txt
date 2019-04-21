project(minimal)
cmake_minimum_required(VERSION 3.2)
if (POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

find_package(ECM REQUIRED CONFIG)

find_package(Qt5 REQUIRED Core Quick Multimedia Test Widgets QuickControls2 Positioning)
find_package(KF5Kirigami2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src)
