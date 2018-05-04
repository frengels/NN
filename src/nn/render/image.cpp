#include "nn/render/image.hpp"

#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace nn {

image_load_error::image_load_error(const std::string& filename)
    : std::ios_base::failure(std::string("failed to load image: \"") +
                             filename + "\"") {
}

image::image(const std::string_view filename, image::pixel_format f) {
  load(filename, f);
}

image::~image() {
  if (m_image_data) {
    stbi_image_free(m_image_data);
  }
}

void image::load(const std::string_view filename, image::pixel_format f) {
  clear();
  int pixel_format;
  m_image_data = stbi_load(std::data(filename), &m_dimensions.x,
                           &m_dimensions.y, &pixel_format, static_cast<int>(f));

  if (!m_image_data) {
    clear();
    throw image_load_error(std::string(filename));
  }

  if (f == image::pixel_format::DEFAULT) {
    m_pixel_format = static_cast<image::pixel_format>(pixel_format);
  } else {
    m_pixel_format = f;
  }
}

void image::clear() {
  // free last resource
  if (m_image_data) {
    stbi_image_free(m_image_data);
    m_pixel_format = pixel_format::DEFAULT;
    m_dimensions = glm::ivec2(0, 0);
  }
}

size_t image::size() const {
  return static_cast<int>(m_pixel_format) * m_dimensions.x * m_dimensions.y;
}

image::value_type* image::data() {
  return m_image_data;
}
const image::value_type* image::data() const {
  return m_image_data;
}

bool image::empty() const {
  return m_image_data;
}

int image::width() const {
  return m_dimensions.x;
}
int image::height() const {
  return m_dimensions.y;
}
const glm::ivec2& image::dimensions() const {
  return m_dimensions;
}

image::pixel_format image::format() const {
  return m_pixel_format;
}
} // namespace nn