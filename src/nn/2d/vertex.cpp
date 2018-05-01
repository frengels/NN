#include "nn/2d/vertex.hpp"

namespace nn {
vertex::vertex(const glm::vec3& position, const glm::vec2& tex_coords)
    : position(position)
    , tex_coords(tex_coords) {
}

vertex::vertex()
    : vertex(glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)) {
}

vertex_description<2> vertex::description() {
  vertex_description<2> descr = {};
  descr.stride = sizeof(vertex);

  descr.attributes[0].index = 0;
  descr.attributes[0].size =
      sizeof(position) / sizeof(decltype(position)::value_type);
  descr.attributes[0].type = GL_FLOAT;
  descr.attributes[0].normalized = GL_FALSE;
  descr.attributes[0].offset =
      reinterpret_cast<GLvoid*>(offsetof(vertex, position));

  descr.attributes[1].index = 1;
  descr.attributes[1].size =
      sizeof(tex_coords) / sizeof(decltype(tex_coords)::value_type);
  descr.attributes[1].type = GL_FLOAT;
  descr.attributes[1].normalized = GL_FALSE;
  descr.attributes[1].offset =
      reinterpret_cast<GLvoid*>(offsetof(vertex, tex_coords));

  return descr;
}
} // namespace nn