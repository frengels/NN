function(nn_add_test target)
  add_executable(${target} ${ARGN})
  target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIR})
  target_link_libraries(${target} ${Boost_LIBRARIES})
  add_test(${target} ${target})
endfunction()

enable_testing()

nn_add_test(test_component_store test_component_store.cpp)
nn_add_test(test_entity_manager test_entity_manager.cpp)
nn_add_test(test_systems test_systems.cpp)