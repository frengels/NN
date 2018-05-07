#pragma once

#include "nn/render/camera.hpp"

namespace nn {
class orthographic_camera : public camera {
public:
  orthographic_camera(float left, float right, float bottom, float top,
                      float near, float far);

  void adjust(float left, float right, float bottom, float top, float near,
              float far);
};
} // namespace nn