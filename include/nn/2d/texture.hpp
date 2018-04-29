#pragma once

#include <GL/glew.h>

namespace nn {
class texture {
public:
  using size_type = size_t;

private:
  GLuint texture_id;

  size_t m_width;
  size_t m_height;
};
} // namespace nn