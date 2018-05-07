#pragma once

#include <vector>

#include "nn/sg/node_base.hpp"

namespace nn {
class scene : public node_base {
private:
  glm::mat4 m_identity{};
  // camera m_camera;

public:
  scene() = default;
  // scene(const camera& cam);
  virtual const glm::mat4& world_transform() override;
  virtual const glm::mat4& local_transform() override;

  virtual void update() override;
};
} // namespace nn