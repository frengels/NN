cmake_minimum_required(VERSION 3.10)

project(NN CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/modules
    ${CMAKE_MODULE_PATH})

include(Warnings)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(src/nn)
add_subdirectory(examples)