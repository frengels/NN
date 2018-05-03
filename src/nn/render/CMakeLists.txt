set(RENDER_SRC
    egl/window.cpp)

add_library(render ${RENDER_SRC})
target_include_directories(render PRIVATE ${CMAKE_SOURCE_DIR}/include)