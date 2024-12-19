cmake_minimum_required(VERSION 3.27)
project(Lab4SDA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab4SDA
        App.cpp
        IteratorMD.cpp
        IteratorMD.h
        MD.cpp
        MD.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
