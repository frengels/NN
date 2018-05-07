#include "nn/render/camera.hpp"

namespace nn {
camera::~camera() {
}

const glm::mat4& camera::projection() const {
  return m_projection;
}
} // namespace nn