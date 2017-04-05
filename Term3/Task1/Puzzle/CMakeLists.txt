cmake_minimum_required(VERSION 3.6)
project(puzzle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CPuzzle.h CPuzzle.cpp)
add_executable(puzzle ${SOURCE_FILES})