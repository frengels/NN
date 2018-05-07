#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "nn/render/2d/transform.hpp"
#include "nn/sg/node_base.hpp"

namespace nn {
class node2d : public node_base {
public:
  using transform_type = transform;

protected:
  transform_type m_transform;

  glm::mat4 m_cached_local;
  /**
   * parent x local transform
   */
  glm::mat4 m_cached_world;

protected:
  node2d(node_base* parent, const transform_type& transform);
  virtual ~node2d() override;

  virtual void update() override;

  virtual const glm::mat4& world_transform() override;
  virtual const glm::mat4& local_transform() override;
};
} // namespace nn