#pragma once

#include "nn/render/2d/transform.hpp"

namespace nn {
struct transform2d_component {
  nn::transform transform;

  template<typename... Args>
  transform2d_component(Args&&... args)
      : transform(std::forward<Args>(args)...) {
  }
};
} // namespace nn