#pragma once

#include "nn/render/2d/renderable2d.hpp"

namespace nn {
class renderer2d {
public:
  using renderable_type = nn::renderable2d;

private:
  void push(const std::shared_ptr<renderable_type>& r,
            const glm::mat4& transform, int z_layer, float z_offset);
  void flush();
};
} // namespace nn