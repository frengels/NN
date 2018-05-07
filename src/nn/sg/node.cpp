#include "nn/sg/node.hpp"

namespace nn {
node2d::node2d(node_base* parent, const transform_type& transform)
    : node_base{parent}
    , m_transform{transform}
    , m_cached_local{}
    , m_cached_world{m_parent->world_transform()} {
}

void node2d::update() {
  auto parent_transform = m_parent->world_transform();

  m_cached_local = m_transform.transformation();

  m_cached_world = parent_transform * m_cached_local;
}

const glm::mat4& node2d::world_transform() {
  return m_cached_world;
}

const glm::mat4& node2d::local_transform() {
  return m_cached_local;
}
} // namespace nn