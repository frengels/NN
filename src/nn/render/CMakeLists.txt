set(RENDER_SRC
    texture.cpp
    2d/sprite.cpp
    image.cpp
    vertex.cpp
    debug.cpp
    2d/sprite_batch.cpp
    2d/sprite_atlas.cpp
    shader.cpp
    shader_program.cpp
    egl/window.cpp)

add_library(render ${RENDER_SRC})
target_include_directories(render PRIVATE ${CMAKE_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIR})
target_link_libraries(render ${OPENGL_LIBRARY} GLEW::GLEW )