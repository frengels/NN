#include "nn/render/2d/sprite_batch.hpp"

#include <algorithm>
#include <array>
#include <cstring>

#include <glm/gtx/transform.hpp>

#include "nn/render/debug.hpp"
#include "nn/render/vertex.hpp"

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

bool sprite_batch::add(const nn::sprite& spr, const glm::mat4& transformation) {
  // this batch is full
  if ((m_vertex_count + std::size(spr.mesh->vertices)) >
      std::numeric_limits<GLushort>::max()) {
    return false;
  }

  m_vertex_count += spr.mesh->vertices.size();
  m_index_count += spr.mesh->indices.size();
  m_sprites.emplace_back(transformation, spr);
  return true;
}

void sprite_batch::flush(const shader_program& sp, const glm::mat4& mvp) {
  if (std::empty(m_sprites)) {
    return;
  }

  // sort sprites for minimal rebinds
  std::sort(std::begin(m_sprites), std::end(m_sprites),
            [](const auto& lhs, const auto& rhs) -> bool {
              return lhs.second.texture->id() < rhs.second.texture->id();
            });

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

  // vector of indices where we have to change our texture including the texture
  // to be bound
  std::vector<std::pair<GLushort, texture*>> draw_indices;

  if (!std::empty(m_sprites)) {
    draw_indices.emplace_back(distance_i,
                              m_sprites.front().second.texture.get());
  }

  for (const auto& sprite_pair : m_sprites) {
    // if we the sprite is not the same start a new draw call
    if (sprite_pair.second.texture->id() != draw_indices.back().second->id()) {
      draw_indices.emplace_back(distance_i, sprite_pair.second.texture.get());
    }

    std::vector<vertex2d> vertices(
        std::size(sprite_pair.second.mesh->vertices));
    std::vector<GLushort> indices(std::size(sprite_pair.second.mesh->indices));

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
    std::transform(std::begin(sprite_pair.second.mesh->vertices),
                   std::end(sprite_pair.second.mesh->vertices),
                   std::begin(vertices), [&](const auto& v) -> auto {
                     auto res = v;
                     res.position =
                         transformation * glm::vec4(v.position, 0.f, 1.f);
                     return res;
                   });

    std::transform(std::begin(sprite_pair.second.mesh->indices),
                   std::end(sprite_pair.second.mesh->indices),
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

  sp.bind();
  sp.uniform(3, mvp); // set mvp matrix
  sp.uniform(8, 0);   // set texture

  NN_GL_DEBUG(glActiveTexture(GL_TEXTURE0));
  m_sprites[0].second.texture->bind();

  NN_GL_DEBUG(glBindVertexArray(m_vertex_array_object));

  for (auto it = std::begin(draw_indices); it != std::end(draw_indices); ++it) {
    GLuint draw_count;
    if ((it + 1) != std::end(draw_indices)) {
      draw_count = (it + 1)->first - it->first;
    } else {
      draw_count = m_index_count - it->first;
    }
    glActiveTexture(GL_TEXTURE0);
    it->second->bind();
    glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_SHORT,
                   reinterpret_cast<GLvoid*>(it->first));
  }
  /*
  NN_GL_DEBUG(
      glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, nullptr));
*/
  // clear our vectors
  m_sprites.clear();
  m_index_count = 0;
  m_vertex_count = 0;
}
} // namespace nn