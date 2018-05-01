#pragma once

#include <memory>
#include <vector>

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

public:
  std::shared_ptr<texture> texture;
  rectangle<texture::size_type> rect;
  float scale;

  glm::vec2 anchor;

  std::vector<glm::vec2> vertices;
  std::vector<GLushort> indices;

public:
  sprite(const std::shared_ptr<nn::texture>& tex, const rectangle_type& rect);
  const rectangle_type& texture_rect() const;
};
} // namespace nn