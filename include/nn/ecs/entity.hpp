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

  operator bool() const noexcept;

  bool operator==(const entity& other) const noexcept;
};
} // namespace nn