cmake_minimum_required(VERSION 3.6)
project(Hemming)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp COrGraph.h COrGraph.cpp)
add_executable(Hemming ${SOURCE_FILES})