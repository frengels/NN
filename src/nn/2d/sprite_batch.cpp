#include "nn/2d/sprite_batch.hpp"

#include <algorithm>
#include <array>
#include <cstring>

#include <glm/gtx/transform.hpp>

#include "nn/2d/debug.hpp"
#include "nn/2d/vertex.hpp"

namespace nn {
sprite_batch::sprite_batch() {
  auto descriptions = vertex_type::description();

  // allocate buffers
  NN_GL_DEBUG(glGenBuffers(1, &m_vertex_buffer));
  NN_GL_DEBUG(glGenBuffers(1, &m_index_buffer));
  NN_GL_DEBUG(glGenVertexArrays(1, &m_vertex_array_object));

  // setup vao
  NN_GL_DEBUG(glBindVertexArray(m_vertex_array_object));
  NN_GL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));
  NN_GL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer));

  // bind attributes
  for (const auto& attr_descr : descriptions.attributes) {
    NN_GL_DEBUG(glEnableVertexAttribArray(attr_descr.index));
    NN_GL_DEBUG(glVertexAttribPointer(attr_descr.index, attr_descr.size,
                                      attr_descr.type, attr_descr.normalized,
                                      descriptions.stride, attr_descr.offset));
  }
  NN_GL_DEBUG(glBindVertexArray(0));
}

sprite_batch::~sprite_batch() {
  NN_GL_DEBUG(glDeleteVertexArrays(1, &m_vertex_array_object));
  NN_GL_DEBUG(glDeleteBuffers(1, &m_vertex_buffer));
  NN_GL_DEBUG(glDeleteBuffers(1, &m_index_buffer));
}

void sprite_batch::add(const nn::sprite& spr, const glm::mat4& transformation) {
  m_vertex_count += spr.vertices.size();
  m_index_count += spr.indices.size();
  m_sprites.emplace_back(transformation, spr);
}

void sprite_batch::flush() {
  if (std::empty(m_sprites)) {
    return;
  }
  // calculate the total number of vertices

  // TODO: buffer the vertices so that we don't have to wait with uploading
  // whilst the last frame is drawing, probably using GL_MAP_UNSYNCHRONIZED_BIT
  // map our vertex buffer first
  NN_GL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));
  NN_GL_DEBUG(glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(vertex2d),
                           nullptr, GL_STREAM_DRAW));
  vertex2d* buffer_vertices =
      reinterpret_cast<vertex2d*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
  // next map our indices
  NN_GL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer));
  NN_GL_DEBUG(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                           m_index_count * sizeof(GLushort), nullptr,
                           GL_STREAM_DRAW));
  GLushort* buffer_indices = reinterpret_cast<GLushort*>(
      glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

  size_t distance_v = 0;
  size_t distance_i = 0;

  for (const auto& sprite_pair : m_sprites) {
    std::vector<vertex2d> vertices(std::size(sprite_pair.second.vertices));
    std::vector<GLushort> indices(std::size(sprite_pair.second.indices));

    // get the dimensions of our texture so we can calculate translation for the
    // anchor
    const auto& tex_w = static_cast<float>(sprite_pair.second.texture->width());
    const auto& tex_h =
        static_cast<float>(sprite_pair.second.texture->height());

    const auto& anchor = sprite_pair.second.anchor;

    auto anchor_translation =
        glm::translate(glm::vec3(-tex_w * anchor.x, -tex_h * anchor.y, 0.0f));

    auto transformation = sprite_pair.first * anchor_translation;

    // transform each vertex by the transformation matrix
    std::transform(std::begin(sprite_pair.second.vertices),
                   std::end(sprite_pair.second.vertices),
                   std::begin(vertices), [&](const auto& v) -> auto {
                     auto res = v;
                     res.position =
                         transformation * glm::vec4(v.position, 0.f, 1.f);
                     return res;
                   });

    std::transform(std::begin(sprite_pair.second.indices),
                   std::end(sprite_pair.second.indices),
                   std::begin(indices), [&](const auto& i) -> auto {
                     return i + distance_v;
                   });

    std::memcpy(buffer_vertices + distance_v, std::data(vertices),
                std::size(vertices) *
                    sizeof(std::decay_t<decltype(vertices)>::value_type));
    std::memcpy(buffer_indices + distance_i, std::data(indices),
                std::size(indices) *
                    sizeof(std::decay_t<decltype(indices)>::value_type));
    distance_v += std::size(vertices);
    distance_i += std::size(indices);
  }

  NN_GL_DEBUG(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));
  NN_GL_DEBUG(glUnmapBuffer(GL_ARRAY_BUFFER));
  NN_GL_DEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer));
  NN_GL_DEBUG(glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER));

  // TODO: map the texture etc

  NN_GL_DEBUG(glActiveTexture(GL_TEXTURE0));
  m_sprites[0].second.texture->bind();

  NN_GL_DEBUG(glBindVertexArray(m_vertex_array_object));
  NN_GL_DEBUG(
      glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, nullptr));

  // clear our vectors
  m_sprites.clear();
  m_index_count = 0;
  m_vertex_count = 0;
}
} // namespace nn