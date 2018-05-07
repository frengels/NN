#pragma once

#include <glm/glm.hpp>

namespace nn {
class camera {
public:
protected:
  glm::mat4 m_projection;

public:
  camera(const glm::mat4& projection);
  virtual ~camera();

  const glm::mat4& projection() const;
};
} // namespace nn