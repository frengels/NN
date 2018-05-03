#pragma once

#include <array>

#include <GL/glew.h>

#include "nn/2d/sprite.hpp"

namespace nn {
class sprite_batch {
  using vertex_type = vertex2d;

private:
  GLuint m_vertex_buffer;
  GLuint m_index_buffer;
  GLuint m_vertex_array_object;

  // vertex count cached
  size_t m_vertex_count;
  size_t m_index_count;
  std::vector<std::pair<glm::mat4, sprite>> m_sprites;

public:
  sprite_batch();
  ~sprite_batch();

  void add(const sprite& spr, const glm::mat4& transformation);
  void flush();
};
} // namespace nn