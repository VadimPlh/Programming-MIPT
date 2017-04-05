cmake_minimum_required(VERSION 3.6)
project(Puzzle2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp puzzle.h puzzle.cpp)
add_executable(Puzzle2 ${SOURCE_FILES})