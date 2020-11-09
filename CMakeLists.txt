cmake_minimum_required(VERSION 3.18.4)

set (This Suite)

project(${This} C CXX)

enable_testing()

add_subdirectory(googletest)

set(Headers 
    include/board.hpp
    include/move.hpp
    include/attack_set.hpp
    include/make_unmake.hpp
)

set(Sources
    src/move.cpp
    src/main.cpp
    src/board.cpp
    src/attack_set.cpp
    src/make_unmake.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
