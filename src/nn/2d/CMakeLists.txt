add_library(2d
            texture.cpp
            sprite.cpp
            image.cpp
            vertex.cpp
            debug.cpp
            sprite_batch.cpp
            sprite_atlas.cpp
            shader.cpp
            shader_program.cpp)

target_include_directories(2d PRIVATE ${CMAKE_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIR})
target_link_libraries(2d ${OPENGL_LIBRARY} GLEW::GLEW )