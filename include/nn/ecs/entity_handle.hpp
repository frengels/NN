#pragma once

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

  ~entity_handle() {
    m_manager.destroy(m_entity);
  }
};
} // namespace nn