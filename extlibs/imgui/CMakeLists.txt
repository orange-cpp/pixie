cmake_minimum_required(VERSION 3.28)
project(imgui)

add_library(imgui STATIC source/imgui.cpp)
target_include_directories(imgui PUBLIC include)


add_subdirectory(source)
add_subdirectory(extlibs)


target_link_libraries(imgui PRIVATE freetype)