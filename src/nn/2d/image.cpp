#include "nn/2d/image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace nn {
image::image()
    : m_image_data(nullptr)
    , m_dimensions(glm::ivec2(0, 0))
    , m_channels(nn::image::channels::DEFAULT) {
}

bool image::load(const std::string& filename, image::channels comp) {
  clear();
  int channels;
  m_image_data = stbi_load(filename.c_str(), &m_dimensions.x, &m_dimensions.y,
                           &channels, static_cast<int>(comp));

  if (!m_image_data) {
    clear();
    return false;
  }

  if (comp == image::channels::DEFAULT) {
    m_channels = static_cast<image::channels>(channels);
  } else {
    m_channels = comp;
  }

  return true;
}

void image::clear() {
  // free last resource
  if (m_image_data) {
    stbi_image_free(m_image_data);
    m_channels = channels::DEFAULT;
    m_dimensions = glm::ivec2(0, 0);
  }
}

image::~image() {
  if (m_image_data) {
    stbi_image_free(m_image_data);
  }
}

size_t image::size() const {
  return static_cast<int>(m_channels) * m_dimensions.x * m_dimensions.y;
}

image::value_type* image::data() {
  return m_image_data;
}
const image::value_type* image::data() const {
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

image::channels image::channel() const {
  return m_channels;
}
} // namespace nn