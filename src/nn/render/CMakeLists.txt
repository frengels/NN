set(RENDER_SRC
    texture.cpp
    image.cpp
    vertex.cpp
    debug.cpp
    shader.cpp
    shader_program.cpp
    camera.cpp
    2d/orthographic_camera.cpp
    2d/render_batch.cpp
    2d/sprite.cpp
    2d/packed_sprite.cpp
    2d/renderable2d.cpp
    2d/renderer2d.cpp
    2d/transform.cpp)

add_library(render ${RENDER_SRC})
target_include_directories(render PRIVATE ${CMAKE_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIR} ${STBI_INCLUDE_DIR})
target_link_libraries(render ${OPENGL_LIBRARY} GLEW::GLEW glm m)