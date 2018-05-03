#pragma once

#include <vector>

namespace nn {
template<typename V, typename I>
class geometry {
public:
  using vertex_type = V;
  using index_type = I;

public:
  std::vector<vertex_type> vertices;
  std::vector<index_type> indices;

public:
  geometry();
  geometry(const std::vector<vertex_type>& vs,
           const std::vector<index_type>& is)
      : vertices(vs)
      , indices(is) {
  }
  geometry(std::vector<vertex_type>&& vs, std::vector<index_type>&& is)
      : vertices(std::move(vs))
      , indices(std::move(is)) {
  }
  template<typename VInputIt, typename IInputIt>
  geometry(VInputIt vfirst, VInputIt vlast, IInputIt ifirst, IInputIt ilast)
      : vertices(vfirst, vlast)
      , indices(ifirst, ilast) {
  }
  geometry(const geometry&) = default;
  geometry(geometry&&) = default;

  geometry& operator=(const geometry&) = default;
};
} // namespace nn