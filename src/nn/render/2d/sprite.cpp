#include "nn/render/2d/sprite.hpp"

namespace nn {
sprite::sprite(const std::shared_ptr<nn::texture>& tex, const srectangle& rect,
               const glm::vec2& anchor, const std::vector<vertex2d>& vertices,
               const std::vector<GLushort>& indices)
    : texture(tex)
    , rect(rect)
    , anchor(anchor)
    , geometry(vertices, indices) {
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex, const srectangle& rect,
               const glm::vec2& anchor)
    : sprite(tex, rect, anchor, {}, {0, 1, 2, 0, 2, 3}) {
  // generate our vertices, these will simply be 2 triangles which cover our
  // rectangle

  assert(tex->width() != 0 && tex->height() != 0);

  float tex_width = static_cast<float>(tex->width());
  float tex_height = static_cast<float>(tex->height());

  float tex_coord_x = static_cast<float>(rect.x) / tex_width;
  float tex_coord_y = static_cast<float>(rect.y) / tex_height;
  float tex_coord_w = static_cast<float>(rect.width) / tex_width;
  float tex_coord_h = static_cast<float>(rect.height) / tex_height;

  geometry.vertices.reserve(4);

  // this might have to be reversed if the coordinate system is wrong

  // bottom left vertex, tex_coord x:0, y:1
  geometry.vertices.emplace_back(
      glm::vec2(0.f, 0.f), glm::vec2(tex_coord_x, tex_coord_y + tex_coord_h));
  // bottom right vertex, tex_coord x:1, y:1
  geometry.vertices.emplace_back(
      glm::vec2(static_cast<float>(rect.width), 0.f),
      glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y + tex_coord_h));
  // upper right vertex, tex_coord x:1, y:0
  geometry.vertices.emplace_back(
      glm::vec2(static_cast<float>(rect.width),
                static_cast<float>(rect.height)),
      glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y));
  // upper left, tex_coord x:0, y:0
  geometry.vertices.emplace_back(
      glm::vec2(0.f, static_cast<float>(rect.height)),
      glm::vec2(tex_coord_x, tex_coord_y));

  // indices were already setup in the constructor
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex, const srectangle& rect)
    : sprite(tex, rect, glm::vec2(0.5f, 0.5f)) {
}

sprite::sprite(const std::shared_ptr<nn::texture>& tex)
    : sprite(tex, srectangle(0, 0, tex->width(), tex->height())) {
}
} // namespace nn