#pragma once

#include <string>

#include <glm/glm.hpp>

namespace nn {
class image {
public:
  using value_type = unsigned char;

  enum class channels {
    DEFAULT = 0,
    GREY = 1,
    GREY_ALPHA = 2,
    RGB = 3,
    RGBA = 4
  };

private:
  unsigned char* m_image_data;

  glm::ivec2 m_dimensions;

  channels m_channels;

public:
  image();
  ~image();

  bool load(const std::string& filename, channels comp);
  void clear();

  size_t size() const;
  value_type* data();
  const value_type* data() const;

  int width() const;
  int height() const;
  const glm::ivec2& dimensions() const;

  image::channels channel() const;
};
} // namespace nn