find_package(GLFW REQUIRED)

add_executable(show_sprite show_sprite.cpp)
target_include_directories(show_sprite PRIVATE ${GLFW_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(show_sprite ${GLFW_LIBRARY} render)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/cat.png ${CMAKE_BINARY_DIR}/textures/cat.png COPYONLY)