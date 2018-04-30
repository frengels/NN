#include "nn/2d/sprite.hpp"

namespace nn {
sprite::sprite(const std::shared_ptr<nn::texture>& tex,
               const sprite::rectangle_type& rect)
    : m_texture(tex), m_rect(rect) {}

const sprite::rectangle_type& sprite::texture_rect() const { return m_rect; }

nn::texture* sprite::texture() { return m_texture.get(); }
const nn::texture* sprite::texture() const { return m_texture.get(); }
} // namespace nn