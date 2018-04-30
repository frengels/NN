#pragma once

#include <memory>

#include "nn/2d/texture.hpp"
#include "nn/stl/rectangle.hpp"

namespace nn {
/**
 * the sprite class represents the information required to draw the sprite on
 * screen. It does not however contain any graphics specific code. That is
 * handled in the sprite renderer
 */
class sprite {
public:
  using rectangle_type = rectangle<texture::size_type>;

private:
  std::shared_ptr<texture> m_texture;
  rectangle<texture::size_type> m_rect;
  float m_scale;

public:
  sprite(const std::shared_ptr<nn::texture>& tex, const rectangle_type& rect);
  const rectangle_type& texture_rect() const;

  nn::texture* texture();
  const nn::texture* texture() const;
  float scale() const;
  void set_scale(float f);
};
} // namespace nn