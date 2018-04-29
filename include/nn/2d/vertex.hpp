#pragma once

#include <glm/glm.hpp>

namespace nn {
struct vertex {
  glm::vec3 position;
  glm::vec2 tex_coords;

  vertex(const glm::vec3 &position, const glm::vec2 &tex_coords);
  vertex();
};
} // namespace nn