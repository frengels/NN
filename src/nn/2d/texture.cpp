#include "nn/2d/texture.hpp"

#include <cassert>

#include "nn/2d/debug.hpp"

namespace nn {
texture::texture(const image& img, texture::wrap wrap_mode)
    : m_texture_id(0)
    , m_width(img.width())
    , m_height(img.height())
    , m_wrap(wrap_mode) {
  // generate our texture
  NN_GL_DEBUG(glGenTextures(1, &m_texture_id));
  // set wrapping mode
  set_wrapping_mode(m_wrap);

  assert(static_cast<int>(img.channel()) == 4);

  NN_GL_DEBUG(glBindTexture(GL_TEXTURE_2D, m_texture_id));

  // setup filters

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // upload texture
  NN_GL_DEBUG(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
                           GL_RGBA, GL_UNSIGNED_BYTE, std::data(img)));
}
texture::texture(const image& img)
    : texture(img, wrap::REPEAT) {
}

texture::~texture() {
  if (m_texture_id) {
    NN_GL_DEBUG(glDeleteTextures(1, &m_texture_id));
  }
}

GLuint texture::id() const {
  return m_texture_id;
}

size_t texture::width() const {
  return m_width;
}

size_t texture::height() const {
  return m_height;
}

void texture::bind() const {
  NN_GL_DEBUG(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}

texture::wrap texture::wrapping_mode() const {
  return m_wrap;
}

void texture::set_wrapping_mode(texture::wrap w) {
  NN_GL_DEBUG(glBindTexture(GL_TEXTURE_2D, m_texture_id));
  NN_GL_DEBUG(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(w)));
  NN_GL_DEBUG(
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, static_cast<GLint>(w)));

  m_wrap = w;
}

} // namespace nn