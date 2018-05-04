#pragma once

#include <ios>
#include <string>

#include <glm/glm.hpp>

namespace nn {

class image_load_error : public std::ios_base::failure {
public:
  image_load_error(const std::string& file);
};

class image {
public:
  using value_type = unsigned char;

  enum class pixel_format {
    DEFAULT = 0,
    GREY = 1,
    GREY_ALPHA = 2,
    RGB = 3,
    RGBA = 4
  };

private:
  unsigned char* m_image_data{nullptr};

  glm::ivec2 m_dimensions{0.f, 0.f};

  pixel_format m_pixel_format{pixel_format::DEFAULT};

public:
  image() = default;
  image(const std::string_view filename, pixel_format f = pixel_format::RGBA);
  ~image();

  void load(const std::string_view filename,
            pixel_format f = pixel_format::RGBA);
  void clear();

  size_t size() const;
  value_type* data();
  const value_type* data() const;
  bool empty() const;

  int width() const;
  int height() const;
  const glm::ivec2& dimensions() const;

  image::pixel_format format() const;
};
} // namespace nn