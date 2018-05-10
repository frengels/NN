#pragma once

#include <cassert>
#include <queue>
#include <tuple>
#include <vector>

#include "nn/ecs/component_store.hpp"
#include "nn/ecs/entity.hpp"

namespace nn {
template<typename... Components>
class entity_manager {
  using entity_type = nn::entity;

private:
  std::vector<uint32_t> m_entities;
  std::priority_queue<uint32_t> m_free_index;

  std::tuple<component_store<Components>...> m_component_stores;

public:
  entity_manager() = default;

  nn::entity create() {
    // case where free entities are queued
    if (!std::empty(m_free_index)) {
      auto index = m_free_index.top();
      m_free_index.pop();

      auto version = m_entities[index];

      nn::entity res = {};
      res.id = index;
      res.version = version;

      return res;
    }

    // case where all entity slots are taken
    else {
      m_entities.emplace_back(0);
      nn::entity res(std::size(m_entities) - 1, 0);
      return res;
    }
  }

  template<typename C>
  void attach(const nn::entity& ent, const C& component) {
    // crash if invalid entity
    assert(valid(ent));

    std::get<component_store<C>>(m_component_stores).push(ent, component);
  }

  template<typename C, typename... Args>
  void attach_emplace(const nn::entity& ent, Args&&... args) {
    assert(valid(ent));
    std::get<component_store<C>>(m_component_stores)
        .emplace(ent, std::forward<Args>(args)...);
  }

  template<typename C>
  C* get(const nn::entity& ent) {
    return std::get<component_store<C>>(m_component_stores).get(ent);
  }

  bool valid(const nn::entity& ent) {
    if (std::size(m_entities) <= ent.id) {
      return false;
    }

    auto current_version = m_entities[ent.id];
    return current_version == ent.version;
  }
};
} // namespace nn