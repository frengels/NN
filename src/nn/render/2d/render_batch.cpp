#include "nn/render/2d/render_batch.hpp"

namespace nn {
render_batch::render_batch() {
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ibo);
}

render_batch::~render_batch() {
  if (m_vbo) {
    glDeleteBuffers(1, &m_vbo);
  }

  if (m_ibo) {
    glDeleteBuffers(1, &m_ibo);
  }

  if (m_vao) {
    glDeleteVertexArrays(1, &m_vao);
  }
}
} // namespace nn