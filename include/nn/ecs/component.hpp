#pragma once

#include "nn/ecs/entity.hpp"

namespace nn {
template<typename T>
struct component {
  using component_type = T;
  using value_type = component_type;
  using key_type = nn::entity;

  key_type m_entity;
  component_type component;

  component(const entity& ent, const component_type& c)
      : m_entity(ent)
      , component(c) {
  }

  template<typename... Args>
  component(const entity& ent, Args... args)
      : m_entity(ent)
      , component(std::forward<Args>(args)...) {
  }

  const nn::entity& entity() const {
    return m_entity;
  }
};
} // namespace nn