#pragma once

#include "nn/render/mesh.hpp"
#include "nn/render/texture.hpp"

namespace nn {
template<typename T>
struct clip {
  T x;
  T y;

  T width;
  T height;

  clip(const T& x, const T& y, const T& width, const T& height)
      : x(x)
      , y(y)
      , width(width)
      , height(height) {
  }

  template<typename V, typename I>
  mesh<V, I> generate_mesh(const texture& tex) const {
    float tex_width = static_cast<float>(tex.width());
    float tex_height = static_cast<float>(tex.height());

    float tex_coord_x = static_cast<float>(x) / tex_width;
    float tex_coord_y = static_cast<float>(y) / tex_height;
    float tex_coord_w = static_cast<float>(width) / tex_width;
    float tex_coord_h = static_cast<float>(height) / tex_height;

    std::vector<I> indices{0, 1, 2, 0, 2, 3};
    std::vector<V> vertices;
    vertices.reserve(4);

    // bottom left vertex, tex_coord x:0, y:1
    vertices.emplace_back(glm::vec2(0.f, 0.f),
                          glm::vec2(tex_coord_x, tex_coord_y + tex_coord_h));
    // bottom right vertex, tex_coord x:1, y:1
    vertices.emplace_back(
        glm::vec2(static_cast<float>(width), 0.f),
        glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y + tex_coord_h));
    // upper right vertex, tex_coord x:1, y:0
    vertices.emplace_back(
        glm::vec2(static_cast<float>(width), static_cast<float>(height)),
        glm::vec2(tex_coord_x + tex_coord_w, tex_coord_y));
    // upper left, tex_coord x:0, y:0
    vertices.emplace_back(glm::vec2(0.f, static_cast<float>(height)),
                          glm::vec2(tex_coord_x, tex_coord_y));

    return mesh<V, I>(std::move(vertices), std::move(indices));
  }

  friend void swap(clip<T>& lhs, clip<T>& rhs) {
    std::swap(lhs.x, rhs.x);
    std::swap(lhs.y, rhs.y);
    std::swap(lhs.width, rhs.width);
    std::swap(lhs.height, rhs.height);
  }
};

typedef clip<size_t> stclip;
typedef clip<uint64_t> ui64clip;
typedef clip<uint32_t> ui32clip;
typedef clip<uint16_t> ui16clip;
typedef clip<uint8_t> ui8clip;
} // namespace nn