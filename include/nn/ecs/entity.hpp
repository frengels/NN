#pragma once

#include <cstdint>
#include <limits>

namespace nn {
struct entity {
public:
  using id_type = uint32_t;
  using version_type = uint32_t;

  static constexpr id_type INVALID_ID = std::numeric_limits<id_type>::max();

public:
  id_type id{INVALID_ID};
  version_type version{0};

  entity() = default;
  entity(id_type id, version_type v)
      : id{id}
      , version{v} {
  }

  bool operator==(const entity& other) const noexcept {
    return id == other.id && version == other.version;
  }
};
} // namespace nn