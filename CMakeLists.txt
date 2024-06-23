cmake_minimum_required(VERSION 3.28)

project(pixie)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}")
option(BUILD_WITH_CODE_VIRTUALIZER "Build with CodeVirtulizer support" OFF)

add_library(pixie MODULE source/main.cpp)

add_subdirectory(extlibs)
add_subdirectory(source)

target_link_libraries(pixie PRIVATE titanfall2-sdk imgui)

if (BUILD_WITH_CODE_VIRTUALIZER)
    target_compile_definitions(pixie PRIVATE USE_CV)
    target_link_libraries(pixie PRIVATE cv-sdk)
else ()
    target_compile_definitions(pixie PRIVATE VIRTUALIZER_START VIRTUALIZER_END)
endif ()