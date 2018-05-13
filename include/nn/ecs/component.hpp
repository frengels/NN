#pragma once

#include "nn/ecs/entity.hpp"

namespace nn {
template<typename T>
struct component {
  using component_type = T;
  using value_type = component_type;
  using key_type = nn::entity;

private:
  key_type m_entity;

public:
  component_type value;

  component(const entity& ent, const component_type& c)
      : m_entity(ent)
      , value(c) {
  }

  template<typename... Args>
  component(const entity& ent, Args&&... args)
      : m_entity(ent)
      , value(std::forward<Args>(args)...) {
  }

  const nn::entity& entity() const {
    return m_entity;
  }

  friend void swap(component<T>& lhs, component<T>& rhs) {
    using std::swap;
    swap(lhs.m_entity, rhs.m_entity);
    swap(lhs.value, rhs.value);
  }
};
} // namespace nn