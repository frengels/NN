#pragma once

#include <memory>
#include <vector>

#include <boost/container/flat_map.hpp>

#include "nn/render/2d/sprite.hpp"
#include "nn/render/texture.hpp"

namespace nn {
struct sprite_description {
  srectangle rect;
  glm::vec2 anchor;
  std::vector<vertex2d> vertices;
  std::vector<GLushort> indices;
};

class sprite_atlas {
private:
  std::shared_ptr<texture> m_texture;

  boost::container::flat_map<std::string, sprite_description> m_sprites;

public:
  sprite_atlas(const std::shared_ptr<texture>& tex,
               boost::container::flat_map<std::string, sprite_description>&&
                   descriptions);

  std::unique_ptr<sprite> create(std::string_view name) const;
};
} // namespace nn