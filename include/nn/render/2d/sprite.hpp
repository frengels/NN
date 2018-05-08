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

private:
  glm::vec2 m_anchor;
  stclip m_clip;

public:
public:
  /**
   * calculates mesh from clip and sets your anchor relative to the clipping
   * points
   */
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect,
         const glm::vec2& anchor);
  /**
   * calculates mesh from clip
   */
  sprite(const std::shared_ptr<nn::texture>& tex, const stclip& rect);
  /**
   *  uses the entire texture as clip
   */
  sprite(const std::shared_ptr<nn::texture>& tex);
  sprite(const sprite&) = default;
  sprite(sprite&&) = default;

  sprite& operator=(const sprite&) = default;

  const stclip& clip() const;

  const glm::vec2& anchor() const;
  void set_anchor(const glm::vec2& a);
};
} // namespace nn