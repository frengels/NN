set(SG_SRC
    node2d.cpp)

add_library(sg ${SG_SRC})
target_include_directories(sg PRIVATE ${CMAKE_SOURCE_DIR}/include)