cmake_minimum_required(VERSION 3.10)

project(NekoNeko CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)

add_subdirectory(src/nn)