find_package(glfw3 REQUIRED)

add_executable(show_sprite show_sprite.cpp)
target_include_directories(show_sprite PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(show_sprite glfw render fswatch pthread)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/cat.png ${CMAKE_BINARY_DIR}/textures/cat.png COPYONLY)