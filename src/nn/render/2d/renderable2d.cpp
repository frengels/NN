#include "nn/render/2d/renderable2d.hpp"

namespace nn {
renderable2d::renderable2d(const mesh_type& mesh, const glm::vec2& offset,
                           const std::shared_ptr<nn::texture>& tex)
    : mesh{mesh}
    , offset{offset}
    , texture{tex} {
}

renderable2d::~renderable2d() {
}
} // namespace nn