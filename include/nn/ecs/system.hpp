#pragma once

#include <functional>

#include "nn/ecs/entity_manager.hpp"

namespace nn {
template<typename EntityManager, typename ComponentFunc>
class system {
public:
  using entity_manager_type = EntityManager;
  // using function_type = std::function<void(entity_manager_type&, float)>;
  using function_type = ComponentFunc;

protected:
  function_type m_func;

public:
  system(function_type func)
      : m_func{func} {
  }

  void operator()(entity_manager_type& manager, float dt) {
    m_func(manager, dt);
  }
};

template<typename EntityManager, typename ComponentFunc>
nn::system<EntityManager, ComponentFunc> make_system(ComponentFunc func) {
  return nn::system<EntityManager, ComponentFunc>(func);
}
} // namespace nn