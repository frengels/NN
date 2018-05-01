#pragma once

#include <GL/glew.h>

#include "nn/2d/image.hpp"

namespace nn {
class texture {
public:
  using size_type = size_t;

  enum class wrap {
    REPEAT = GL_REPEAT,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
  };

private:
  GLuint m_texture_id;
  size_t m_width;
  size_t m_height;

  wrap m_wrap;

public:
  texture(const image& img, wrap wrap_mode);
  texture(const image& img);
  ~texture();

  GLuint id() const;

  size_t width() const;
  size_t height() const;

  void bind() const;

  wrap wrapping_mode() const;
  void set_wrapping_mode(wrap w);
};
} // namespace nn