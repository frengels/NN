#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "nn/ecs/entity_manager.hpp"

struct entity_manager_fixture {
  nn::entity_manager<float, int, std::string> test_manager;
  nn::entity entity1;
  nn::entity entity2;
  nn::entity entity3;

  entity_manager_fixture() {
    entity1 = test_manager.create();
    entity2 = test_manager.create();
    entity3 = test_manager.create();
  }
};

BOOST_FIXTURE_TEST_SUITE(test_entity_manager, entity_manager_fixture)

BOOST_AUTO_TEST_CASE(create_empty_entities) {

  auto entity4 = test_manager.create();
  BOOST_REQUIRE(test_manager.get<float>(entity4) == nullptr);
  BOOST_REQUIRE(test_manager.get<int>(entity4) == nullptr);
  BOOST_REQUIRE(test_manager.get<std::string>(entity4) == nullptr);
}

BOOST_AUTO_TEST_CASE(attach_components) {
  test_manager.attach(entity1, 73);
  BOOST_REQUIRE(test_manager.get<float>(entity1) == nullptr);
  BOOST_REQUIRE(*test_manager.get<int>(entity1) == 73);
  BOOST_REQUIRE(test_manager.get<std::string>(entity1) == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()