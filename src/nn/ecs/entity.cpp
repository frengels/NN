#include "nn/ecs/entity.hpp"

namespace nn {
entity::operator bool() const noexcept {
  return !valid || id == INVALID_ID;
}

bool entity::operator==(const entity& other) const noexcept {
  return id == other.id && version == other.version && valid == other.valid;
}
} // namespace nn