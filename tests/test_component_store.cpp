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

  nn::entity test_entity(0, 0, true);

  test_component test1(73, "Trinky");

  test_store.push(test_entity, test1);
}