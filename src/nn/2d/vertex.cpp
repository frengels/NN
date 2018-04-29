#include "nn/2d/vertex.hpp"

namespace nn {
vertex::vertex(const glm::vec3 &position, const glm::vec2 &tex_coords)
    : position(position), tex_coords(tex_coords) {}

vertex::vertex() : vertex(glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)) {}
} // namespace nn