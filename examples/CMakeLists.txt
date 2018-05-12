find_package(glfw3 REQUIRED)

add_executable(show_sprite show_sprite.cpp)
target_include_directories(show_sprite PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(show_sprite glfw render ${CMAKE_THREAD_LIBS_INIT})

if(NOT WIN32)
  target_link_libraries(show_sprite fswatch)
endif(NOT WIN32)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/cat.png ${CMAKE_BINARY_DIR}/textures/cat.png COPYONLY)