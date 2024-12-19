cmake_minimum_required(VERSION 3.27)
project(Seminar3_GestiuneMelodii_CPP2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Seminar3_GestiuneMelodii_CPP2
        main.cpp
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        Song.cpp
        Song.h
        UI.cpp
        UI.h
        validators.h)
