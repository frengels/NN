#include "nn/sg/scene.hpp"

namespace nn {

const glm::mat4& scene::world_transform() {
  return m_identity;
}

const glm::mat4& scene::local_transform() {
  return m_identity;
}

void scene::update() {
  // do nothing we're the root
}
} // namespace nn