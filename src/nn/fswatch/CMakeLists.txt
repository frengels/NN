set(FSWATCH_SRC
    fs_monitor.cpp)

add_library(fswatch ${FSWATCH_SRC})
target_link_libraries(fswatch spdlog::spdlog stdc++fs)
target_include_directories(fswatch PRIVATE ${CMAKE_SOURCE_DIR}/include)