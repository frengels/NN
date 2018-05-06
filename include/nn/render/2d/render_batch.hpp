#pragma once

#include <GL/glew.h>

#include "nn/render/2d/renderable2d.hpp"

namespace nn {
class render_batch {
  using renderable_type = renderable2d;
  using vertex_type = renderable_type::index_type;
  using index_type = renderable_type::vertex_type;

private:
  GLuint m_vbo;
  GLuint m_ibo;
  GLuint m_vao;

  vertex_type* m_mapped_vertices;
  index_type* m_mapped_indices;

public:
  render_batch();
  ~render_batch();
};
} // namespace nn