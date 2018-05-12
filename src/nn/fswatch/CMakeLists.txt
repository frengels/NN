set(FSWATCH_SRC
    fs_monitor.cpp)


if(NOT WIN32)
  add_library(fswatch ${FSWATCH_SRC})
  target_link_libraries(fswatch spdlog::spdlog stdc++fs)
  target_include_directories(fswatch PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif(NOT WIN32)
  