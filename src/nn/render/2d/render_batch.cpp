#include "nn/render/2d/render_batch.hpp"

#include "nn/render/shader_program.hpp"

namespace nn {
render_batch::render_batch() {
  // generate and bind buffers
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glGenBuffers(1, &m_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

  // bind attributes etc
  auto attr_descr = vertex2d::description();
  for (const auto& descr : attr_descr.attributes) {
    glEnableVertexAttribArray(descr.index);
    glVertexAttribPointer(descr.index, descr.size, descr.type, descr.normalized,
                          attr_descr.stride, descr.offset);
  }
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

void render_batch::begin(size_t v_size, size_t i_size) {

  // orphan our buffers
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_type) * v_size, nullptr,
               GL_STREAM_DRAW);
  m_mapped_vertices = reinterpret_cast<vertex_type*>(
      glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_type) * i_size, nullptr,
               GL_STREAM_DRAW);
  m_mapped_indices = reinterpret_cast<index_type*>(
      glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void render_batch::end() {
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glUnmapBuffer(GL_ARRAY_BUFFER);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
  glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

  // for safety
  m_mapped_vertices = nullptr;
  m_mapped_indices = nullptr;
}

void render_batch::flush() {
  // no set up happens in here, render batches simply aggregate vertices and
  // indices
  glBindVertexArray(m_vao);
  glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_SHORT, nullptr);

  m_num_indices = 0;
  m_num_vertices = 0;
}

size_t render_batch::vertices_count() const {
  return m_num_vertices;
}

size_t render_batch::indices_count() const {
  return m_num_indices;
}
} // namespace nn