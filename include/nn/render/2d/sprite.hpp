#pragma once

#include <memory>
#include <vector>

#include "nn/render/2d/renderable2d.hpp"
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
class sprite : public renderable2d {
public:
  using renderable2d::index_type;
  using renderable2d::mesh_type;
  using renderable2d::vertex_type;

public:
  glm::vec2 anchor;
  stclip clip;

public:
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
         const glm::vec2& anchor, mesh_type&& mesh);
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
         const glm::vec2& anchor);
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect);
  sprite(const std::shared_ptr<nn::texture>& tex);
  sprite(const sprite&) = default;
  sprite(sprite&&) = default;

  sprite& operator=(const sprite&) = default;
};
} // namespace nn