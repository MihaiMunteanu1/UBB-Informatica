cmake_minimum_required(VERSION 3.27)
project(LAB2_4__ C)

set(CMAKE_C_STANDARD 11)

add_executable(LAB2_4__ main.c
        domain.h
        domain.c
        customsort.c
        customsort.h
        repository.c
        repository.h
        service.c
        service.h)
