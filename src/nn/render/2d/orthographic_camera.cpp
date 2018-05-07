#include "nn/render/2d/orthographic_camera.hpp"

#include <glm/gtx/transform.hpp>

namespace nn {
orthographic_camera::orthographic_camera(float left, float right, float bottom,
                                         float top, float near, float far)
    : camera{glm::ortho(left, right, bottom, top, near, far)} {
}

void orthographic_camera::adjust(float left, float right, float bottom,
                                 float top, float near, float far) {
  m_projection = glm::ortho(left, right, bottom, top, near, far);
}
} // namespace nn