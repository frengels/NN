#pragma once

#include <limits>
#include <stdint.h>

namespace nn {
struct entity {
public:
  using id_type = uint32_t;
  using version_type = uint16_t;

  static constexpr id_type INVALID_ID = std::numeric_limits<id_type>::max();

public:
  id_type id{INVALID_ID};
  version_type version{0};
  bool valid{false};

  entity() = default;
  entity(id_type id, version_type v, bool valid = true)
      : id{id}
      , version{v}
      , valid{valid} {
  }

  operator bool() const noexcept {
    return id != INVALID_ID && valid;
  }

  bool operator==(const entity& other) const noexcept {
    return id == other.id && version == other.version && valid == other.valid;
  }
};
} // namespace nn