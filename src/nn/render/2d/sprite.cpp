#include "nn/render/2d/sprite.hpp"

namespace nn {
sprite::sprite(const std::shared_ptr<nn::texture>& tex, const stclip& clip,
               const glm::vec2& anchor, mesh_type&& mesh)
    : renderable2d{mesh, tex}
    , anchor{anchor}
    , clip{clip} {
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex, const stclip& clip,
               const glm::vec2& anchor)
    : sprite(tex, clip, anchor, mesh_type({}, {0, 1, 2, 0, 2, 3})) {
  // generate our vertices, these will simply be 2 triangles which cover our
  // rectangle

  assert(tex->width() != 0 && tex->height() != 0);

  float tex_width = static_cast<float>(tex->width());
  float tex_height = static_cast<float>(tex->height());

  float tex_coord_x = static_cast<float>(clip.x) / tex_width;
  float tex_coord_y = static_cast<float>(clip.y) / tex_height;
  float tex_coord_w = static_cast<float>(clip.width) / tex_width;
  float tex_coord_h = static_cast<float>(clip.height) / tex_height;

  mesh.vertices.reserve(4);

  // this might have to be reversed if the coordinate system is wrong

  // bottom left vertex, tex_coord x:0, y:1
  mesh.vertices.emplace_back(glm::vec2(0.f, 0.f),
                             glm::vec2(tex_coord_x, tex_coord_y + tex_coord_h));
  // bottom right vertex, tex_coord x:1, y:1
  mesh.vertices.emplace_back(
      glm::vec2(static_cast<float>(clip.width), 0.f),
      glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y + tex_coord_h));
  // upper right vertex, tex_coord x:1, y:0
  mesh.vertices.emplace_back(glm::vec2(static_cast<float>(clip.width),
                                       static_cast<float>(clip.height)),
                             glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y));
  // upper left, tex_coord x:0, y:0
  mesh.vertices.emplace_back(glm::vec2(0.f, static_cast<float>(clip.height)),
                             glm::vec2(tex_coord_x, tex_coord_y));

  // indices were already setup in the constructor
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex, const stclip& clip)
    : sprite(tex, clip, glm::vec2(0.5f, 0.5f)) {
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex)
    : sprite(tex, stclip(0, 0, tex->width(), tex->height())) {
}
} // namespace nn