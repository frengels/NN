#pragma once

#include <tuple>

#include "nn/ecs/component.hpp"

namespace nn {
/**
 * convenience class to help iterate over multiple components at the same time
 * allows .get<C> rather than having to use .get<component<C>>
 */
template<typename... Cs>
class component_view {
public:
  template<typename C>
  using component_type = component<C>;

private:
  std::tuple<component<Cs>*...> m_components;

public:
  constexpr component_view(component_type<Cs>*... components)
      : m_components{components...} {
  }

  template<typename C>
  inline constexpr component_type<C>* get() {
    return std::get<component_type<C>*>(m_components);
  }
}; // namespace nn
} // namespace nn