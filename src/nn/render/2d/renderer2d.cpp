#include "nn/render/2d/renderer2d.hpp"

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
} // namespace nn