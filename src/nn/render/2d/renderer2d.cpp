#include "nn/render/2d/renderer2d.hpp"

#include <algorithm>

#include <glm/gtx/transform.hpp>

namespace nn {
void renderer2d::push(const renderable2d& r, const glm::mat4& transform,
                      int z_layer, float z_offset) {
  render_info info{r, transform, z_layer, z_offset};

  m_renderables.push_back(info);
}

void renderer2d::flush() {

  // nothing to do
  if (std::empty(m_renderables)) {
    return;
  }

  // sort all renderables by layer > depth > texture
  std::sort(std::begin(m_renderables), std::end(m_renderables),
            [](const auto& lhs, const auto& rhs) -> bool {
              if (lhs.z_layer == rhs.z_layer) {
                if (lhs.z_offset == rhs.z_offset) {
                  return lhs.renderable.get().texture->id() <
                         rhs.renderable.get().texture->id();
                }
                return lhs.z_offset < rhs.z_offset;
              }
              return lhs.z_layer < rhs.z_layer;
            });

  // loop through all renderables to set up our batch sizes first
  // renderables, vertices, indices
  std::vector<GLuint> texture_ids;
  std::vector<std::tuple<size_t, size_t, size_t>> batch_sizes;
  size_t current_renderable_count = 0;
  size_t current_v_count = 0;
  size_t current_i_count = 0;
  GLuint current_texture = m_renderables[0].renderable.get().texture->id();
  texture_ids.push_back(current_texture);
  for (size_t i = 0; i < std::size(m_renderables); ++i) {
    const auto& render_info = m_renderables[i];

    // start new batch
    if (render_info.renderable.get().texture->id() != current_texture) {
      batch_sizes.emplace_back(std::make_tuple(
          current_renderable_count, current_v_count, current_i_count));
      current_renderable_count = 1;
      current_v_count = std::size(render_info.renderable.get().mesh.vertices);
      current_i_count = std::size(render_info.renderable.get().mesh.indices);
      current_texture = render_info.renderable.get().texture->id();
      texture_ids.push_back(current_texture);
    } else {
      ++current_renderable_count;
      current_v_count += std::size(render_info.renderable.get().mesh.vertices);
      current_i_count += std::size(render_info.renderable.get().mesh.indices);
    }
  }

  batch_sizes.push_back(std::make_tuple(current_renderable_count,
                                        current_v_count, current_i_count));

  // set some queryable info
  m_vertex_count = current_v_count;
  m_index_count = current_i_count;

  // divide into batches
  std::vector<render_batch*> batches;
  render_batch* current_batch{nullptr};

  // use the count for going through our renderable list
  current_renderable_count = 0;
  for (size_t i = 0; i < std::size(batch_sizes); ++i) {
    current_batch = m_batch_pool.acquire();
    current_batch->begin(std::get<1>(batch_sizes[i]),
                         std::get<2>(batch_sizes[i]));

    // iterate through our renderables
    for (size_t n = current_renderable_count;
         n < (std::get<0>(batch_sizes[i]) + current_renderable_count); ++n) {
      current_batch->push(
          m_renderables[n].renderable.get().mesh,
          m_renderables[n].transformation *
              glm::translate(
                  glm::vec3(m_renderables[n].renderable.get().offset, 0.f)));
    }

    current_batch->end();
    batches.push_back(current_batch);
    current_renderable_count += std::get<0>(batch_sizes[i]);
  }

  m_batch_count = std::size(batches);

  assert(std::size(batches) == std::size(texture_ids));

  glActiveTexture(GL_TEXTURE0);
  for (size_t i = 0; i < std::size(batches); ++i) {
    glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
    batches[i]->flush();
    m_batch_pool.release(batches[i]);
  }

  m_renderables.clear();
}
} // namespace nn