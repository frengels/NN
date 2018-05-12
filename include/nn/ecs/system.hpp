#pragma once

#include <functional>

#include "nn/ecs/ecs_traits.hpp"
#include "nn/ecs/entity_manager.hpp"

namespace nn {
template<typename EntityManager, typename F>
class system {
public:
  using entity_manager_type = EntityManager;
  // using function_type = std::function<void(entity_manager_type&, float)>;
  using function_type = F;

protected:
  function_type m_func;

public:
  system(function_type func)
      : m_func{func} {
  }

  void operator()(entity_manager_type& manager,
                  float dt) noexcept(noexcept(m_func(manager, dt))) {
    m_func(manager, dt);
  }
};

template<typename EntityManager, typename F>
nn::system<EntityManager, F> make_system([[maybe_unused]] const EntityManager&,
                                         F func) {
  return nn::system<EntityManager, F>(func);
}

template<typename EntityManager, typename F, typename... Cs>
class constexpr_system {
public:
  using function_type = F;
  using entity_manager_type = EntityManager;

private:
  function_type m_func;

public:
  constexpr_system(function_type func)
      : m_func{func} {
  }

  void operator()([[maybe_unused]] entity_manager_type& manager,
                  [[maybe_unused]] float dt) noexcept(noexcept(m_func(manager,
                                                                      dt))) {
    if constexpr (nn::entity_manager_has_components<entity_manager_type,
                                                    Cs...>::value) {
      m_func(manager, dt);
    } else {
      // do nothing if it doesn't contain our required components
    }
  }
};

template<typename... Cs, typename EntityManager, typename F>
nn::constexpr_system<EntityManager, F, Cs...>
make_constexpr_system(const EntityManager&, F func) {
  return nn::constexpr_system<EntityManager, F, Cs...>(func);
}

template<typename EntityManager, typename F, typename C, typename... Cs>
class iterating_constexpr_system {
public:
  using entity_manager_type = EntityManager;
  using function_type = F;

private:
  function_type m_func;

public:
  iterating_constexpr_system(function_type func)
      : m_func{func} {
  }

  void operator()([[maybe_unused]] entity_manager_type& manager,
                  [[maybe_unused]] float dt) noexcept(noexcept(m_func(manager,
                                                                      dt))) {
  }
};

} // namespace nn