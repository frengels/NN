#pragma once

#include <vector>

#include "nn/render/2d/render_batch.hpp"
#include "nn/render/2d/renderable2d.hpp"
#include "nn/stl/movable_object_pool.hpp"

namespace nn {
class renderer2d {
public:
  struct render_info {

    std::shared_ptr<renderable2d> renderable;
    glm::mat4 transformation;
    int z_layer;
    float z_offset;
  };

  using renderable_type = nn::renderable2d;

private:
  std::vector<render_info> m_renderables;
  movable_object_pool<render_batch> m_batch_pool;

  size_t m_batch_count;
  size_t m_vertex_count;
  size_t m_index_count;

public:
  renderer2d() = default;

  void push(const std::shared_ptr<renderable_type>& r,
            const glm::mat4& transform, int z_layer, float z_offset);
  void flush();
};
} // namespace nn