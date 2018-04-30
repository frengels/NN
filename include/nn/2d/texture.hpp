#pragma once

#include <GL/glew.h>

#include "nn/2d/image.hpp"

namespace nn {
class texture {
public:
  using size_type = size_t;

private:
  GLuint m_texture_id;

  size_t m_width;
  size_t m_height;

public:
  texture(const image &img);
  ~texture();
};
} // namespace nn