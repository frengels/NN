#include "nn/sg/node2d.hpp"

namespace nn {
node2d::node2d(node_base* parent, const transform_type& transform)
    : node_base{parent}
    , m_transform{transform}
    , m_cached_local{m_transform.transformation()}
    , m_cached_world{m_parent->world_transform() * m_cached_local}
    , m_dirty{false} {
}

void node2d::update() {
  auto parent_transform = m_parent->world_transform();

  m_cached_local = m_transform.transformation();

  m_cached_world = parent_transform * m_cached_local;
  m_dirty = false;
}

const glm::mat4& node2d::world_transform() {
  if (m_dirty) {
    update();
  }
  return m_cached_world;
}

const glm::mat4& node2d::local_transform() {
  if (m_dirty) {
    update();
  }
  return m_cached_local;
}

void node2d::translate(const glm::vec2& translation) {
  m_transform.position += translation;
  m_dirty = true;
}

void node2d::rotate(float angle) {
  m_transform.angle += angle;
  m_dirty = true;
}

void node2d::scale(const glm::vec2& scale) {
  m_transform.scale *= scale;
  m_dirty = true;
}
} // namespace nn