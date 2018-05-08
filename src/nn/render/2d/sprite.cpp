#include "nn/render/2d/sprite.hpp"

namespace nn {
sprite::sprite(const std::shared_ptr<nn::texture>& tex, const stclip& clip,
               const glm::vec2& anchor)
    : renderable2d(clip.generate_mesh<vertex_type, index_type>(*tex),
                   glm::vec2(), tex)
    , m_anchor{anchor}
    , m_clip{clip} {
  set_anchor(m_anchor);
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex, const stclip& clip)
    : sprite(tex, clip, glm::vec2(0.5f, 0.5f)) {
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex)
    : sprite(tex, stclip(0, 0, tex->width(), tex->height())) {
}

const stclip& sprite::clip() const {
  return m_clip;
}

const glm::vec2& sprite::anchor() const {
  return m_anchor;
}

void sprite::set_anchor(const glm::vec2& a) {
  m_anchor = a;
  float clip_w = static_cast<float>(m_clip.width);
  float clip_h = static_cast<float>(m_clip.height);
  offset = glm::vec2(-clip_w * m_anchor.x, -clip_h * m_anchor.y);
}
} // namespace nn