#include "nn/render/2d/renderer2d.hpp"

#include <algorithm>

namespace nn {
void renderer2d::push(const std::shared_ptr<renderable2d>& r,
                      const glm::mat4& transform, int z_layer, float z_offset) {
  render_info info = {};
  info.renderable = r;
  info.transformation = transform;
  info.z_layer = z_layer;
  info.z_offset = z_offset;

  m_renderables.push_back(info);
}

void renderer2d::flush() {

  if (std::empty(m_renderables)) {
    return;
  }

  // sort all renderables by depth and layer
  std::sort(std::begin(m_renderables), std::end(m_renderables),
            [](const auto& lhs, const auto& rhs) -> bool {
              if (lhs.z_layer == rhs.z_layer) {
                if (lhs.z_offset == rhs.z_offset) {
                  return lhs.renderable->texture->id() <
                         rhs.renderable->texture->id();
                }
                return lhs.z_offset < rhs.z_offset;
              }
              return lhs.z_layer < rhs.z_layer;
            });

  // divide into batches
  std::vector<render_batch*> batches;

  GLuint tex_id{m_renderables[0].renderable->texture->id()};
  render_batch* current_batch{m_batch_pool.acquire()};

  for (const auto& render_info : m_renderables) {
    // start preparing a new batch if we've got a new texture
    if (render_info.renderable->texture->id() != tex_id) {
      batches.push_back(current_batch);
      current_batch = m_batch_pool.acquire();
    }
  }
}
} // namespace nn