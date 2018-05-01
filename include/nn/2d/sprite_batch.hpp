#pragma once

#include <array>

#include <GL/glew.h>

#include "nn/2d/sprite.hpp"

namespace nn {
class sprite_batch {
private:
  std::array<GLuint, 2> m_vertex_buffers;
  std::array<GLuint, 2> m_index_buffers;
  std::array<GLuint, 2> m_vertex_array_objects;

  size_t m_sprites;

public:
  sprite_batch();
  ~sprite_batch();

  void add(const sprite& spr, const glm::mat4& transformation);
};
} // namespace nn