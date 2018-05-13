#pragma once

#include <glm/glm.hpp>

namespace nn {
struct transform {
  glm::vec2 position{0.0f, 0.0f};
  glm::vec2 scale{1.0f, 1.0f};
  float angle{0.0f};
  /**
   * layer where this is located at, used to decide draw order
   */
  int z_layer{0};

  /**
   * offset within the layer
   */
  float z_offset{0.0f};

  transform() = default;
  transform(const glm::vec2& pos, const glm::vec2& scale, float angle = 0.0f,
            int z_layer = 0, float z_offset = 0.0f);

  float angle_deg() const;

  glm::mat4 transformation() const;
};
} // namespace nn