#include "nn/render/2d/transform.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

namespace nn {
float transform::angle_deg() const {
  return glm::degrees(angle);
}

glm::mat4 transform::transformation() const {
  auto scale_mat = glm::scale(glm::vec3(scale, 1.f));
  auto rot_mat = glm::rotate(angle, glm::vec3(0.f, 0.f, 1.f));
  auto translate_mat = glm::translate(glm::vec3(position, 0.f));

  return translate_mat * rot_mat * scale_mat;
}
} // namespace nn