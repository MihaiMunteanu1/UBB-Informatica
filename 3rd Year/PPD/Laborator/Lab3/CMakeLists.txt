cmake_minimum_required(VERSION 3.20)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)


add_executable(Lab3
        secv.cpp
        v1.1.cpp
        v1.1.cpp
        v2.2.cpp
        v3.3.cpp
)

target_link_libraries(Lab3 PRIVATE MPI::MPI_CXX)

