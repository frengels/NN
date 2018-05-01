#include "nn/2d/sprite_batch.hpp"

#include <array>

#include "nn/2d/debug.hpp"
#include "nn/2d/vertex.hpp"

namespace nn {
sprite_batch::sprite_batch()
    : m_sprites(0) {
  auto descriptions = vertex::description();

  // allocate buffers
  NN_GL_DEBUG(
      glGenBuffers(std::size(m_vertex_buffers), std::data(m_vertex_buffers)));
  NN_GL_DEBUG(
      glGenBuffers(std::size(m_index_buffers), std::data(m_index_buffers)));
  NN_GL_DEBUG(glGenVertexArrays(std::size(m_vertex_array_objects),
                                std::data(m_vertex_array_objects)));

  // setup vaos
  for (size_t i = 0; i < std::size(m_vertex_array_objects); ++i) {
    NN_GL_DEBUG(glBindVertexArray(m_vertex_array_objects[i]));
    NN_GL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffers[i]));
    NN_GL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffers[i]));

    // bind attributes
    for (const auto& attr_descr : descriptions.attributes) {
      NN_GL_DEBUG(glEnableVertexAttribArray(attr_descr.index));
      NN_GL_DEBUG(glVertexAttribPointer(
          attr_descr.index, attr_descr.size, attr_descr.type,
          attr_descr.normalized, descriptions.stride, attr_descr.offset));
    }
  }
}

sprite_batch::~sprite_batch() {
  NN_GL_DEBUG(glDeleteVertexArrays(std::size(m_vertex_array_objects),
                                   std::data(m_vertex_array_objects)));
  NN_GL_DEBUG(glDeleteBuffers(std::size(m_vertex_buffers),
                              std::data(m_vertex_buffers)));
  NN_GL_DEBUG(
      glDeleteBuffers(std::size(m_index_buffers), std::data(m_index_buffers)));
}

void sprite_batch::add(const sprite& spr, const glm::mat4& transformation) {
}
} // namespace nn