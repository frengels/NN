#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "nn/ecs/entity_handle.hpp"
#include "nn/ecs/entity_manager.hpp"
#include "nn/ecs/system.hpp"

struct system_test_fixture {
  nn::entity_manager<float, long, int, std::string> test_manager;

  std::unique_ptr<nn::entity_handle<decltype(test_manager)>> entities[4];

  system_test_fixture() {
    float current_float{0.0f};
    long current_long{5};
    int current_int{0};
    std::string current_string{"a"};
    for (size_t i = 0; i < std::size(entities); ++i) {
      entities[i] = nn::make_entity_unique(test_manager);

      test_manager.attach<float>(entities[i]->entity(), current_float);
      test_manager.attach<long>(entities[i]->entity(), current_long);
      test_manager.attach<int>(entities[i]->entity(), current_int);
      test_manager.attach<std::string>(entities[i]->entity(), current_string);

      current_float += 10.0f;
      current_long += 20;
      current_int += 10;
      current_string += "a";
    }
  }
};

BOOST_FIXTURE_TEST_SUITE(test_entity_systems, system_test_fixture)

BOOST_AUTO_TEST_CASE(iterate_components) {
  // ints go 0, 10, 20, 30
  int current{0};
  for (auto it = test_manager.begin<int>(); it != test_manager.end<int>();
       ++it) {
    BOOST_REQUIRE(it->value == current);
    current += 10;
  }
}

// test iteration with a system
BOOST_AUTO_TEST_CASE(system_iteration) {
  auto integer_system = nn::make_system<decltype(test_manager)>(
      [](auto& manager, [[maybe_unused]] float dt) {
        manager.template for_each<int>([](auto& v) { v = 0; });
      });

  auto integer10_system = nn::make_system<decltype(test_manager)>(
      [](auto& manager, [[maybe_unused]] float dt) {
        for (auto it = manager.template begin<int>();
             it != manager.template end<int>(); ++it) {
          it->value = 10;
        }
      });

  integer_system(test_manager, 0.0f);

  for (auto it = test_manager.begin<int>(); it != test_manager.end<int>();
       ++it) {
    BOOST_REQUIRE(it->value == 0);
  }

  integer10_system(test_manager, 0.0f);

  for (auto it = test_manager.begin<int>(); it != test_manager.end<int>();
       ++it) {
    BOOST_REQUIRE(it->value == 10);
  }
}

BOOST_AUTO_TEST_SUITE_END()