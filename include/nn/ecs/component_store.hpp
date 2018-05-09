#pragma once

#include <cassert>

#include "nn/ecs/component.hpp"
#include "nn/ecs/entity.hpp"

namespace nn {
/**
 * since most entities will not have a specific component
 */
template<typename C>
class component_store {
public:
  using entity_type = nn::entity;
  using key_type = entity_type;
  using component_type = component<C>;
  using value_type = component_type;
  using store_type = std::vector<C>;

  static constexpr size_t INVALID_HANDLE = std::numeric_limits<size_t>::max();

private:
  /**
   * tightly packed store of components for cache efficiency
   */
  store_type m_components;
  /**
   * holds a handle to the location where the component is located within the
   * components array
   */
  std::vector<entity_type::id_type> m_entries;

public:
  void push(const entity& ent, const component_type& c) {
    // make sure the entity is valid
    // should be disabled in release mode
    assert(ent);
    _check_size(ent);

    // insert into the back and take that index for our entry
    m_components.push_back(c);
    auto index = std::size(m_components) - 1;
    m_entries[ent.id] = static_cast<entity_type::id_type>(index);
  }

  template<typename... Args>
  void emplace(const entity& ent, Args&&... args) {
    assert(ent);
    _check_size(ent);

    m_components.emplace_back(std::forward<Args>(args)...);
    auto index = std::size(m_components) - 1;
    m_entries[ent.id] = static_cast<entity_type::id_type>(index);
  }

  void remove(const entity& ent) {
    assert(ent.id);
    auto dense_index = m_entries[ent.id];
  }

  void contains(const entity& ent) {
    auto handle = m_entries[ent.id];
    if (handle == INVALID_HANDLE) {
      return false;
    } else {
      return m_components[handle].key() == ent;
    }
  }

private:
  inline void _check_size(const entity& ent) {
    if ((ent.id) >= std::size(m_entries)) {
      // initialize with invalid handle
      m_entries.resize(ent.id, INVALID_HANDLE);
    }
  }
};
} // namespace nn