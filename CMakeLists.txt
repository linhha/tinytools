cmake_minimum_required(VERSION 3.10)

# set the project name
project(tinytools VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
include_directories("/home/liha/.local/include")
link_directories("/home/liha/.local/lib")
link_libraries(tinyxml2)

add_executable(xmlprn xmlprn.cxx)
add_executable(xmlset xmlset.cxx)
