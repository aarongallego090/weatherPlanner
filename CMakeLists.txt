cmake_minimum_required(VERSION 3.20)
project(weatherPlanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(weatherPlanner
        src/heap.cpp
        src/heap.h
        src/main.cpp
        src/ui.cpp
        src/ui.h)