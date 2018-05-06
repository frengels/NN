#pragma once

#include <memory>
#include <vector>

#include "nn/render/mesh.hpp"
#include "nn/render/texture.hpp"
#include "nn/render/vertex.hpp"
#include "nn/stl/clip.hpp"

namespace nn {
/**
 * the sprite class represents the information required to draw the sprite on
 * screen. It does not however contain any graphics specific code. That is
 * handled in the sprite renderer
 */
class sprite {
public:
  using vertex_type = vertex2d;
  using index_type = GLushort;
  using mesh_type = nn::mesh<vertex_type, index_type>;

public:
  std::shared_ptr<nn::texture> texture;
  mesh_type mesh;

  stclip clip;

  glm::vec2 anchor;

public:
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
         const glm::vec2& anchor, const std::vector<vertex_type>& vertices,
         const std::vector<index_type>& indices);
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
         const glm::vec2& anchor);
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect);
  sprite(const std::shared_ptr<nn::texture>& tex);
  sprite(const sprite&) = default;
  sprite(sprite&&) = default;

  sprite& operator=(const sprite&) = default;
};
} // namespace nn