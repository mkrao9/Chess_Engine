cmake_minimum_required(VERSION 3.18.4)

set(This AllTests)

set(Sources
    BoardConstructorTest.cpp
    TestDetermineCheck.cpp
    TestMoveGeneration.cpp
    TestMakeMove.cpp
    TestUnmake.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC 
    gtest_main
    Suite
)

add_test(
    NAME ${This}
    COMMAND ${This}
)