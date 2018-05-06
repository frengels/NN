#pragma once

#include <vector>

#include "nn/render/vertex_traits.hpp"

namespace nn {
template<typename V, typename I>
class mesh {
  static_assert(is_vertex<V>::value, "V must be a vertex type");

public:
  using vertex_type = V;
  using index_type = I;

public:
  std::vector<vertex_type> vertices;
  std::vector<index_type> indices;

public:
  mesh();
  mesh(const std::vector<vertex_type>& vs, const std::vector<index_type>& is)
      : vertices(vs)
      , indices(is) {
  }
  mesh(std::vector<vertex_type>&& vs, std::vector<index_type>&& is)
      : vertices(std::move(vs))
      , indices(std::move(is)) {
  }
  template<typename VInputIt, typename IInputIt>
  mesh(VInputIt vfirst, VInputIt vlast, IInputIt ifirst, IInputIt ilast)
      : vertices(vfirst, vlast)
      , indices(ifirst, ilast) {
  }
  mesh(const mesh&) = default;
  mesh(mesh&&) = default;

  mesh& operator=(const mesh&) = default;
  mesh& operator=(mesh&&) = default;
};
} // namespace nn