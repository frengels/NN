#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace nn {
class node {
private:
  glm::vec3 m_position;
  glm::vec3 m_scale;
  glm::quat m_rotation;

  node* m_parent;
  bool m_dirty;

public:
  node();

  virtual void emplace_node();
};
} // namespace nn