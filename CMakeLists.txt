cmake_minimum_required(VERSION 3.8)

set(This OperativeResearch)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

add_library(${This} STATIC src/*)

add_subdirectory(src/test)
