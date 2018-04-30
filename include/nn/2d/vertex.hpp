#pragma once

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace nn {

struct attribute_description {
  GLuint index;
  GLint size;
  GLenum type;
  GLboolean normalized;
  const GLvoid* offset;
};

template<size_t N>
struct vertex_description {
  GLsizei stride;
  std::array<attribute_description, N> attributes;
};

struct vertex {
  glm::vec3 position;
  glm::vec2 tex_coords;

  vertex(const glm::vec3& position, const glm::vec2& tex_coords);
  vertex();

  static vertex_description<2> description();
};
} // namespace nn