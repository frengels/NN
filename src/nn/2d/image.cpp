#include "nn/2d/image.hpp"

namespace nn {
image::image(const std::string& filename, image::channels components) {
  int file_channels;
  m_image_data = stbi_load(filename.c_str(), &m_dimensions.x, &m_dimensions.y,
                           &file_channels, static_cast<int>(components));

  if (components == image::channels::DEFAULT) {
    m_channels = static_cast<image::channels>(file_channels);
  }
}

size_t image::size() const {
  return static_cast<int>(m_channels) * m_dimensions.x * m_dimensions.y;
}

image::value_type* image::data() { return m_image_data; }
const image::value_type* image::data() const { return m_image_data; }

int image::width() const { return m_dimensions.x; }
int image::height() const { return m_dimensions.y; }
const glm::ivec2& image::dimensions() const { return m_dimensions; }

image::channels image::channel() const { return m_channels; }
} // namespace nn