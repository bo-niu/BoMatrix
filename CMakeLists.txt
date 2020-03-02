cmake_minimum_required(VERSION 3.15)
project(BoMatrix)

set(CMAKE_CXX_STANDARD 11)

add_executable(BoMatrix main.cpp Matrix.hpp BoMatrix.h)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(BoMatrix PUBLIC OpenMP::OpenMP_CXX)
endif()