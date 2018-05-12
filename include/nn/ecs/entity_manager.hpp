#pragma once

#include <cassert>
#include <queue>
#include <tuple>
#include <vector>

#include "nn/ecs/component_store.hpp"
#include "nn/ecs/component_view.hpp"
#include "nn/ecs/entity.hpp"
#include "nn/ecs/utility.hpp"

namespace nn {
template<typename... Components>
class entity_manager {
  using entity_type = nn::entity;
  using tuple_type = std::tuple<component_store<Components>...>;

  template<typename C>
  using store_type = component_store<C>;

  template<typename C>
  using component_iterator = typename component_store<C>::iterator;
  template<typename C>
  using component_const_iterator = typename component_store<C>::const_iterator;

private:
  std::vector<uint32_t> m_entities;
  std::priority_queue<uint32_t> m_free_index;

  tuple_type m_component_stores;

public:
  entity_manager() = default;

  template<typename C>
  component_iterator<C> begin() {
    return std::begin(std::get<component_store<C>>(m_component_stores));
  }

  template<typename C>
  component_iterator<C> end() {
    return std::end(std::get<component_store<C>>(m_component_stores));
  }

  template<typename C>
  component_const_iterator<C> cbegin() {
    return std::cbegin(std::get<component_store<C>>(m_component_stores));
  }

  template<typename C>
  component_const_iterator<C> cend() {
    return std::cend(std::get<component_store<C>>(m_component_stores));
  }

  template<typename C, class UnaryFunction>
  void for_each(UnaryFunction f) {
    for (auto it = begin<C>(); it != end<C>(); ++it) {
      f(*it);
    }
  }

  template<typename... Cs, class Function>
  void for_each_view(Function f) {
    auto view_vector = view_array<Cs...>();

    for (auto& view : view_vector) {
      f(view);
    }
  }

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

  void destroy(const nn::entity& ent) {
    // do nothing if the entity is invalid
    if (ent.id == entity_type::INVALID_ID) {
      return;
    }
    assert(valid(ent));

    // remove all components from stores
    (remove<Components>(ent), ...);
    // increment version to invalidate all remaining entities
    m_entities[ent.id] = ent.version + 1;
    m_free_index.push(ent.id);
  }

  template<typename C>
  void attach(const nn::entity& ent, const C& component) {
    // crash if invalid entity
    assert(valid(ent));

    _store<C>().push(ent, component);
  }

  template<typename C>
  void remove(const nn::entity& ent) {
    assert(valid(ent));

    _store<C>().remove(ent);
  }

  template<typename C, typename... Args>
  void attach_emplace(const nn::entity& ent, Args&&... args) {
    assert(valid(ent));
    _store<C>().emplace(ent, std::forward<Args>(args)...);
  }

  template<typename C>
  component<C>* get(const nn::entity& ent) {
    return _store<C>().get(ent);
  }

  template<typename... Cs>
  component_view<Cs...> get_view(const nn::entity& ent) noexcept {
    return component_view<Cs...>(get<Cs>(ent)...);
  }

  template<typename... Cs>
  std::vector<component_view<Cs...>> view_array() noexcept {
    auto length{std::numeric_limits<size_t>::max()};

    // find the shortest store
    nn::for_each_tuple(m_component_stores, [&](const auto& store) {
      if (std::size(store) < length) {
        length = std::size(store);
      }
    });

    // now that we have found the shortest store, request an array of entities
    // from this store so we can construct our array of views
    std::vector<nn::entity> entity_vector;
    bool shortest_found{false};

    nn::for_each_tuple(m_component_stores, [&](auto& store) {
      if (!shortest_found && (std::size(store) == length)) {
        entity_vector = store.entities();
        shortest_found = true;
      }
    });

    // iterate over this entity list and construct a view list
    std::vector<component_view<Cs...>> views;
    views.reserve(length);

    for (const auto& entity : entity_vector) {
      views.push_back(this->get_view<Cs...>(entity));
    }

    return views;
  }

  template<typename C>
  size_t size() const {
    return std::size(_store<C>());
  }

  size_t size() const {
    return std::size(m_entities) - std::size(m_free_index);
  }

  bool valid(const nn::entity& ent) {
    if (std::size(m_entities) <= ent.id) {
      return false;
    }

    auto current_version = m_entities[ent.id];
    return current_version == ent.version;
  }

private:
  template<typename C>
  inline constexpr component_store<C>& _store() {
    return std::get<component_store<C>>(m_component_stores);
  }

  template<typename C>
  inline constexpr const component_store<C>& _store() const {
    return std::get<component_store<C>>(m_component_stores);
  }
}; // namespace nn
} // namespace nn