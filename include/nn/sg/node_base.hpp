#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace nn {
class node_base {
protected:
  std::vector<node_base> m_children;

  bool m_visible{true};

public:
  node_base() = default;
  virtual ~node_base() = 0;

  virtual const glm::mat4& world_transform();
  virtual const glm::mat4& local_transform();

  virtual void update();
};
} // namespace nn