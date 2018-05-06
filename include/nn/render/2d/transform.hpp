#pragma once

#include <glm/glm.hpp>

namespace nn {
struct transform {
  glm::vec2 position;
  glm::vec2 scale;
  float angle;

  float angle_deg() const;

  glm::mat4 calculate_matrix() const;
};
} // namespace nn