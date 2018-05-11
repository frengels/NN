#pragma once

#include <functional>

#include "nn/ecs/entity_manager.hpp"

namespace nn {
template<typename EntityManager>
class system {
public:
  using entity_manager_type = EntityManager;
  using function_type = std::function<void(entity_manager_type&, float)>;

protected:
  function_type m_func;

public:
  system(function_type&& func)
      : m_func{std::move(func)} {
  }

  void operator()(entity_manager_type& manager, float dt) {
    m_func(manager, dt);
  }
};
} // namespace nn