cmake_minimum_required(VERSION 4.1)
project(weatherPlanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(weatherPlanner
        heap.cpp
        heap.h
        main.cpp)
