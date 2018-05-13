#include "nn/render/utility.hpp"

namespace nn {
void swap(glm::vec2& lhs, glm::vec2& rhs) {
  using std::swap;
  swap(lhs.x, rhs.x);
  swap(lhs.y, rhs.y);
}
}