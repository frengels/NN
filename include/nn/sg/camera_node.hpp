#pragma once

#include "nn/render/camera.hpp"
#include "nn/sg/node_base.hpp"

namespace nn {
class camera_node : public node_base {
private:
public:
  virtual nn::camera* camera();
};
} // namespace nn