#pragma once

#include <stdint.h>

namespace nn {
struct entity {
  uint32_t id;
  uint16_t version;
  bool valid;
};
} // namespace nn