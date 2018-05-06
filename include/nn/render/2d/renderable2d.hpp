#pragma once

#include <memory>

#include "nn/render/mesh.hpp"
#include "nn/render/texture.hpp"
#include "nn/render/vertex.hpp"

namespace nn {
class renderable2d {
public:
  using vertex_type = vertex2d;
  using index_type = GLushort;
  using mesh_type = mesh<vertex_type, index_type>;

private:
  mesh_type mesh;
  std::shared_ptr<nn::texture> texture;

public:
  renderable2d(const mesh_type& mesh, const std::shared_ptr<nn::texture>& tex);
  virtual ~renderable2d();
};
} // namespace nn