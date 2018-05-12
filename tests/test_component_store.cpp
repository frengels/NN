#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <string>

#include "nn/ecs/component_store.hpp"

struct test_component {
  int bestint;
  std::string meme;

  test_component(int i, const std::string& str)
      : bestint{i}
      , meme{str} {
  }
};

BOOST_AUTO_TEST_CASE(insert_remove) {
  nn::component_store<test_component> test_store;

  nn::entity test_entity(0, 0);

  test_component test1(73, "Trinky");

  test_store.push(test_entity, test1);

  auto test1_ptr = test_store.get(test_entity);

  BOOST_REQUIRE(test1.bestint == test1_ptr->value.bestint);
  BOOST_REQUIRE(test1.meme.compare(test1_ptr->value.meme) == 0);
}