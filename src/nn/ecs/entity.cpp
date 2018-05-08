#include "nn/ecs/entity.hpp"

namespace nn {
entity::operator bool() const noexcept {
  return !valid || id == 0;
}
} // namespace nn