cmake_minimum_required(VERSION 3.20)
project(Lab6InClass LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MPI REQUIRED)

add_executable(Lab6InClass main.cpp)
target_link_libraries(Lab6InClass PRIVATE MPI::MPI_CXX)