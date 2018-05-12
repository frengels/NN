#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

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
  using component_type = C;
  using value_type = component<component_type>;
  using store_type = std::vector<value_type>;
  using iterator = typename store_type::iterator;
  using const_iterator = typename store_type::const_iterator;

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
  iterator begin() {
    return std::begin(m_components);
  }

  iterator end() {
    return std::end(m_components);
  }

  const_iterator cbegin() const {
    return std::cbegin(m_components);
  }

  const_iterator cend() const {
    return std::cend(m_components);
  }

  /**
   * return a vector containing a copy of all entities in this component store
   */
  std::vector<nn::entity> entities() const {
    std::vector<nn::entity> res;
    res.reserve(size());

    for (const auto& component : *this) {
      res.push_back(component.entity());
    }

    return res;
  }

  void push(const entity& ent, const component_type& c) {
    // make sure the entity is valid
    // should be disabled in release mode
    _check_size(ent);

    // insert into the back and take that index for our entry
    m_components.push_back(component<C>(ent, c));
    auto index = std::size(m_components) - 1;
    m_entries[ent.id] = static_cast<entity_type::id_type>(index);
  }

  template<typename... Args>
  void emplace(const entity& ent, Args&&... args) {
    _check_size(ent);

    m_components.emplace_back(ent, std::forward<Args>(args)...);
    auto index = std::size(m_components) - 1;
    m_entries[ent.id] = static_cast<entity_type::id_type>(index);
  }

  void remove(const entity& ent) {
    assert(ent.id != nn::entity::INVALID_ID);

    // if bigger than our entries size then this entity doesn't have a component
    // here
    if (ent.id >= std::size(m_entries)) {
      return;
    }

    auto dense_index = m_entries[ent.id];

    assert(dense_index != nn::entity::INVALID_ID);

    // swap element to be removed with the last element
    std::iter_swap(std::begin(m_components) + dense_index,
                   std::end(m_components) - 1);

    m_components.pop_back();

    // get iterator of swapped component
    auto swapped_it = std::begin(m_components) + dense_index;

    m_entries[ent.id] = nn::entity::INVALID_ID;

    if (swapped_it >= std::end(m_components)) {
      return;
    }

    auto component_entity = swapped_it->entity();
    // make everything reference correctly again
    m_entries[component_entity.id] = dense_index;
  }

  value_type* get(const entity_type& e) {
    if (e.id >= std::size(m_entries)) {
      return nullptr;
    }

    auto dense_index = m_entries[e.id];

    if (dense_index == entity::INVALID_ID) {
      return nullptr;
    }

    return &m_components[dense_index];
  }

  bool contains(const entity& ent) {
    auto handle = m_entries[ent.id];
    if (handle == entity::INVALID_ID) {
      return false;
    } else {
      return m_components[handle].key() == ent;
    }
  }

  size_t size() const {
    return std::size(m_components);
  }

private:
  inline void _check_size(const entity& ent) {
    if ((ent.id) >= std::size(m_entries)) {
      // initialize with invalid handle
      m_entries.resize(static_cast<size_t>(ent.id + 1), entity::INVALID_ID);
    }
  }
};
} // namespace nn