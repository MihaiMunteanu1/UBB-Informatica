cmake_minimum_required(VERSION 4.0)
project(Lab1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab1 main.cpp
        TS.h
        TS.cpp
        mainPart3.cpp
        FIP.h
        FIP.cpp
        AutomateFinite/AFBin.h
        AutomateFinite/AFBin.cpp
        AutomateFinite/AFReal.cpp
        AutomateFinite/AFIdentificatori.cpp
        main2.cpp
        AutomateFinite/AFDec.cpp
)
