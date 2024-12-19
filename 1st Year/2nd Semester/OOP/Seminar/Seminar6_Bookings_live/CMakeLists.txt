cmake_minimum_required(VERSION 3.28)
project(Seminar6_Bookings_live)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Seminar6_Bookings_live
        GUI.cpp
        GUI.h
        main.cpp
        Repo.cpp
        Repo.h
        Rezervare.h
        Service.cpp
        Service.h)
