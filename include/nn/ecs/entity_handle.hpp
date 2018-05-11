#pragma once

#include <memory>

#include "nn/ecs/entity.hpp"
#include "nn/ecs/entity_manager.hpp"

namespace nn {

/**
 * applies raii to entity handles
 */
template<typename EntityManager>
class entity_handle {
public:
  using entity_manager_type = EntityManager;
  using entity_type = nn::entity;
  using value_type = entity_type;

private:
  entity_manager_type& m_manager;
  entity_type m_entity;

public:
  entity_handle(entity_manager_type& manager)
      : m_manager{manager}
      , m_entity{m_manager.create()} {
  }

  entity_handle(entity_handle&& other)
      : m_manager{other.m_manager}
      , m_entity{other.m_entity} {
    // invalidate other entity
    other.m_entity.id = entity_type::INVALID_ID;
  }

  ~entity_handle() {
    m_manager.destroy(m_entity);
  }

  entity_handle& operator=(entity_handle other) {
    swap(*this, other);

    return *this;
  }

  friend void swap(entity_handle& lhs, entity_handle& rhs) {
    std::swap(lhs.m_manager, rhs.m_manager);
    std::swap(lhs.m_entity, rhs.m_entity);
  }
};

template<typename EntityManager>
std::unique_ptr<nn::entity_handle<EntityManager>>
make_entity_unique(EntityManager& manager) {
  return std::make_unique<nn::entity_handle<EntityManager>>(
      entity_handle<EntityManager>(manager));
}

template<typename EntityManager>
std::shared_ptr<nn::entity_handle<EntityManager>>
make_entity_shared(EntityManager& manager) {
  return std::make_shared<nn::entity_handle<EntityManager>>(
      entity_handle<EntityManager>(manager));
}
} // namespace nn