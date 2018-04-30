#include "nn/2d/texture.hpp"

#include <cassert>

#include "nn/2d/debug.hpp"

namespace nn {
texture::texture(const image &img)
    : m_texture_id(0), m_width(img.width()), m_height(img.height()) {
  NN_GL_DEBUG(glGenTextures(1, &m_texture_id));
  NN_GL_DEBUG(glBindTexture(GL_TEXTURE_2D, m_texture_id));

  assert(static_cast<int>(img.channel()) == 4);

  NN_GL_DEBUG(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
                           GL_RGBA, GL_UNSIGNED_BYTE, std::data(img)));
}

texture::~texture() {
  if (m_texture_id) {
    NN_GL_DEBUG(glDeleteTextures(1, &m_texture_id));
  }
}
} // namespace nn