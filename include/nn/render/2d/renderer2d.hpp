#pragma once

#include <vector>

#include "nn/render/2d/render_batch.hpp"
#include "nn/render/2d/renderable2d.hpp"
#include "nn/stl/movable_object_pool.hpp"

namespace nn {
class renderer2d {
public:
  struct render_info {

    std::reference_wrapper<const renderable2d> renderable;
    glm::mat4 transformation;
    int z_layer;
    float z_offset;

    render_info(const renderable2d& r, const glm::mat4& transform, int zlayer,
                float zoffset)
        : renderable{std::cref(r)}
        , transformation{transform}
        , z_layer{zlayer}
        , z_offset{zoffset} {
    }
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

  void push(const renderable_type& r, const glm::mat4& transform, int z_layer,
            float z_offset);
  void flush();
};
} // namespace nn