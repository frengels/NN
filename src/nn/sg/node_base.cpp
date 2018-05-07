#include "nn/sg/node_base.hpp"

#include <algorithm>

namespace nn {
bool node_base::destroy_child(node_base* node) {
  // find our node in the vector of children
  auto node_pos = std::find_if(std::begin(m_children), std::end(m_children),
                               [&](const auto& unique_node) -> bool {
                                 return unique_node.get() == node;
                               });

  // return false if the node wasn't found
  if (node_pos == std::end(m_children)) {
    return false;
  }

  // with this all children of the node are destroyed too
  m_children.erase(node_pos);
  return true;
  // TODO: specialised function which removed the node but keeps children alive
  // by attaching them to the parent
}
} // namespace nn