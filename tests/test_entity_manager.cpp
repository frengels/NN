#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "nn/ecs/entity_manager.hpp"

BOOST_AUTO_TEST_CASE(create_entities) {
  nn::entity_manager<float, int, std::string> test_manager;

  auto entity1 = test_manager.create();
  BOOST_REQUIRE(test_manager.get<float>(entity1) == nullptr);
  BOOST_REQUIRE(test_manager.get<int>(entity1) == nullptr);
  BOOST_REQUIRE(test_manager.get<std::string>(entity1) == nullptr);
}