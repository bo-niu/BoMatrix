#project(LibBoMatrix
#        VERSION 1.0
#        DESCRIPTION "Bo's simple matrix library"
#        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

add_library(LibBoMatrix INTERFACE)
target_include_directories(LibBoMatrix INTERFACE include)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(LibBoMatrix INTERFACE OpenMP::OpenMP_CXX)
endif()