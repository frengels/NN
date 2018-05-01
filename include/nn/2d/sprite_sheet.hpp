#pragma once

#include <memory>
#include <vector>

#include <boost/container/flat_map.hpp>

#include "nn/2d/sprite.hpp"
#include "nn/2d/texture.hpp"

namespace nn {
struct sprite_description {
  sprite::rectangle_type rect;
  glm::vec2 anchor;
  std::vector<vertex2d> vertices;
  std::vector<GLushort> indices;
};

class sprite_sheet {
private:
  std::shared_ptr<texture> m_texture;

  boost::container::flat_map<std::string, sprite_description> m_sprites;

public:
  sprite_sheet(const std::shared_ptr<texture>& tex,
               boost::container::flat_map<std::string, sprite_description>&&
                   descriptions);

  std::unique_ptr<sprite> create(std::string_view name) const;
};
} // namespace nn