#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "nn/ecs/entity_handle.hpp"
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

    test_manager.attach(entity3, 73);
    test_manager.attach(entity3, std::string("Hello world"));
    test_manager.attach(entity3, 73.0f);
  }
};

BOOST_FIXTURE_TEST_SUITE(test_entity_manager, entity_manager_fixture)

// entity creation
BOOST_AUTO_TEST_CASE(create_empty_entities) {

  auto entity4 = test_manager.create();
  BOOST_REQUIRE(test_manager.get<float>(entity4) == nullptr);
  BOOST_REQUIRE(test_manager.get<int>(entity4) == nullptr);
  BOOST_REQUIRE(test_manager.get<std::string>(entity4) == nullptr);
}

// attach a component
BOOST_AUTO_TEST_CASE(attach_components) {
  test_manager.attach(entity1, 73);
  BOOST_REQUIRE(test_manager.get<float>(entity1) == nullptr);
  BOOST_REQUIRE(*test_manager.get<int>(entity1) == 73);
  BOOST_REQUIRE(test_manager.get<std::string>(entity1) == nullptr);
}

// remove a single component
BOOST_AUTO_TEST_CASE(remove_components) {
  test_manager.remove<float>(entity3);

  BOOST_REQUIRE(test_manager.get<float>(entity3) == nullptr);
}

// remove multiple components and see if the component store integrity is
// maintained, effectively testing our swap and pop mechanism
BOOST_AUTO_TEST_CASE(remove_multiple) {
  test_manager.attach<float>(entity1, 35.0f);
  test_manager.attach<float>(entity2, 0.0f);

  BOOST_REQUIRE(test_manager.size<float>() == 3);
  BOOST_REQUIRE(*test_manager.get<float>(entity1) == 35.0f);
  BOOST_REQUIRE(*test_manager.get<float>(entity2) == 0.0f);

  test_manager.remove<float>(entity3);

  BOOST_REQUIRE(test_manager.size<float>() == 2);
  BOOST_REQUIRE(test_manager.get<float>(entity3) == nullptr);
  BOOST_REQUIRE(*test_manager.get<float>(entity1) == 35.0f);
  BOOST_REQUIRE(*test_manager.get<float>(entity2) == 0.0f);

  test_manager.remove<float>(entity2);

  BOOST_REQUIRE(test_manager.size<float>() == 1);
  BOOST_REQUIRE(test_manager.get<float>(entity3) == nullptr);
  BOOST_REQUIRE(test_manager.get<float>(entity2) == nullptr);
  BOOST_REQUIRE(*test_manager.get<float>(entity1) == 35.0f);
}

BOOST_AUTO_TEST_CASE(remove_invalid) {
  // TODO: removing an invalid entity will terminate due to assertion, not sure
  // how to handle this yet
}

// check if entity handles cooperate nicely with smart pointers
BOOST_AUTO_TEST_CASE(create_handler) {
  // unique ptr destroy
  BOOST_REQUIRE(std::size(test_manager) == 3);
  {
    auto handle = nn::make_entity_unique(test_manager);
    BOOST_REQUIRE(std::size(test_manager) == 4);
  }

  // shared ptr destroy
  BOOST_REQUIRE(std::size(test_manager) == 3);
  {
    auto shared_handle = nn::make_entity_shared(test_manager);

    BOOST_REQUIRE(std::size(test_manager) == 4);
  }

  BOOST_REQUIRE(std::size(test_manager) == 3);

  // will keep the reference to not destroy the created entity
  // shared ptr keep alive
  std::shared_ptr<nn::entity_handle<decltype(test_manager)>> ref_keeper;

  {
    auto shared_handle = nn::make_entity_shared(test_manager);
    BOOST_REQUIRE(std::size(test_manager) == 4);
    ref_keeper = shared_handle;
    BOOST_REQUIRE(std::size(test_manager) == 4);
  }

  BOOST_REQUIRE(std::size(test_manager) == 4);

  // unique ptr move
  std::unique_ptr<nn::entity_handle<decltype(test_manager)>> moved_to;

  BOOST_REQUIRE(std::size(test_manager) == 4);
  {
    auto moved_from = nn::make_entity_unique(test_manager);
    BOOST_REQUIRE(std::size(test_manager) == 5);
    moved_to = std::move(moved_from);

    BOOST_REQUIRE(std::size(test_manager) == 5);
  }

  BOOST_REQUIRE(std::size(test_manager) == 5);
}

BOOST_AUTO_TEST_SUITE_END()