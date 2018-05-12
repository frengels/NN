set(SG_SRC
    node_base.cpp
    node2d.cpp
    scene.cpp)

add_library(sg ${SG_SRC})
target_include_directories(sg PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(sg glm)