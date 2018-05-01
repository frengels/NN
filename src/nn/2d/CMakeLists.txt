add_library(2d
            texture.cpp
            sprite.cpp
            image.cpp
            vertex.cpp
            debug.cpp
            sprite_batch.cpp
            sprite_sheet.cpp)

target_include_directories(2d PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(2d GLEW::GLEW)