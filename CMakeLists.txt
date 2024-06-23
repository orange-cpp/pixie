cmake_minimum_required(VERSION 3.28)

project(pixie)

set(CMAKE_CXX_STANDARD 26)

add_library(pixie MODULE source/main.cpp)

add_subdirectory(extlibs)

target_link_libraries(pixie PRIVATE cv-sdk)