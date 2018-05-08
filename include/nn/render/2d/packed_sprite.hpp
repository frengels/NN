#pragma once

#include "nn/render/2d/sprite.hpp"

namespace nn {
class packed_sprite : public sprite {
public:
  using sprite::index_type;
  using sprite::mesh_type;
  using sprite::vertex_type;

public:
  /**
   * a custom 2d mesh allows for more tightly packed sprites
   */
  packed_sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
                const glm::vec2& anchor, mesh_type&& mesh);
};
} // namespace nn