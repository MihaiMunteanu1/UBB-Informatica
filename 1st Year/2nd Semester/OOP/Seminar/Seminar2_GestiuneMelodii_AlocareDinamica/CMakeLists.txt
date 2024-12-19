cmake_minimum_required(VERSION 3.27)
project(Seminar2_GestiuneMelodii_AlocareDinamica C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Seminar2_GestiuneMelodii_AlocareDinamica
        melodie.c
        melodie.h
        mylist.c
        mylist.h
        service.c
        service.h
        ui.c
        validator.c
        validator.h)
