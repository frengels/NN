#pragma once

#include <string>

#include <glm/glm.hpp>
#include <stb/stb_image.h>

namespace nn {
class image {
public:
  using value_type = unsigned char;

  enum class channels {
    DEFAULT = STBI_default,
    GREY = STBI_grey,
    GREY_ALPHA = STBI_grey_alpha,
    RGB = STBI_rgb,
    RGBA = STBI_rgb_alpha
  };

private:
  unsigned char* m_image_data;

  glm::ivec2 m_dimensions;

  channels m_channels;

public:
  image(const std::string& filename, channels comp);
  ~image();

  size_t size() const;
  value_type* data();
  const value_type* data() const;

  int width() const;
  int height() const;
  const glm::ivec2& dimensions() const;

  image::channels channel() const;
};
} // namespace nn