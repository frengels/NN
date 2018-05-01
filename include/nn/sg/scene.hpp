#pragma once

#include <vector>

#include "nn/sg/node.hpp"

namespace nn {
class scene : public node {
  std::vector<node> m_nodes;
};
} // namespace nn