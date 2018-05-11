#pragma once

#include <GL/glew.h>

#include "nn/render/2d/renderable2d.hpp"

namespace nn {
class render_batch {
  using renderable_type = renderable2d;
  using mesh_type = renderable_type::mesh_type;
  using vertex_type = renderable_type::vertex_type;
  using index_type = renderable_type::index_type;

private:
  GLuint m_vbo;
  GLuint m_ibo;
  GLuint m_vao;

  vertex_type* m_mapped_vertices{nullptr};
  index_type* m_mapped_indices{nullptr};

  GLsizei m_num_vertices{0};
  GLsizei m_num_indices{0};

public:
  render_batch();
  render_batch(render_batch&& other) noexcept;
  ~render_batch();

  void begin(size_t v_size, size_t i_size);
  void end();
  void push(const mesh_type& mesh, const glm::mat4& transform);

  size_t vertices_count() const;
  size_t indices_count() const;

  void flush();
};
} // namespace nn