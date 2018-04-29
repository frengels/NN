#pragma once

#include <memory>

#include "nn/2d/texture.hpp"
#include "nn/stl/rectangle.hpp"

namespace nn {
class sprite {
private:
  std::shared_ptr<texture> m_texture;
  rectangle<texture::size_type> m_rect;
};
} // namespace nn