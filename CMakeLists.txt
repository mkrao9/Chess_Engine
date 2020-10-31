cmake_minimum_required(VERSION 3.18.4)

set (This Suite)

project(${This} C CXX)

enable_testing()

add_subdirectory(googletest)

set(Headers 
    include/board.hpp
)

set(Sources
    src/main.cpp
    src/board.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
