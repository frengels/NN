#pragma once

#include <vector>

#include "nn/render/2d/renderable2d.hpp"

namespace nn {
class renderer2d {
public:
  struct render_info {

    std::shared_ptr<renderable2d> renderable;
    glm::mat4 transformation;
    int z_layer;
    float z_offset;
  };

  using renderable_type = nn::renderable2d;

private:
  std::vector<render_info> m_renderables;

public:
  renderer2d() = default;

  void push(const std::shared_ptr<renderable_type>& r,
            const glm::mat4& transform, int z_layer, float z_offset);
  void flush();
};
} // namespace nn