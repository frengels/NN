#include "nn/render/2d/packed_sprite.hpp"

namespace nn {
packed_sprite::packed_sprite(const std::shared_ptr<nn::texture>& tex,
                             const stclip& rect, const glm::vec2& anchor,
                             mesh_type&& mesh)
    : sprite(tex, rect, anchor) {
  this->mesh = std::move(mesh);
}
} // namespace nn