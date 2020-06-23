cmake_minimum_required(VERSION 3.15)
project(pruffer_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(pruffer_code
        adjacencyMatrix.h
        pruffer.cpp)
