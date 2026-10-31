cmake_minimum_required(VERSION 3.20)
project(weatherPlanner)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(weatherPlanner
        src/ui.cpp
        src/ui.h
        src/heap.cpp
        src/heap.h
        src/main.cpp
        src/hashtable.cpp
        src/hashtable.h
)

configure_file(${CMAKE_SOURCE_DIR}/projectData.csv ${CMAKE_BINARY_DIR}/projectData.csv COPYONLY)