#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include <glm/glm.hpp>

namespace nn {
class node_base {
protected:
  node_base* m_parent{nullptr};
  std::vector<std::unique_ptr<node_base>> m_children;

  bool m_visible{true};

private:
  /**
   * only used for root component
   */
  node_base() = default;

protected:
  /**
   * should not directly be called, will be called through create_child(...)
   * which takes care of proper ownership
   */
  node_base(node_base* parent);

public:
  virtual ~node_base() = 0;

  virtual const glm::mat4& world_transform() = 0;
  virtual const glm::mat4& local_transform() = 0;

  virtual void update() = 0;

  template<typename T, typename... Args>
  T* create_child(Args&&... args) {
    // make sure it's a valid node
    static_assert(std::is_base_of_v<node_base, T>,
                  "Created node must be derived from base!");

    // create our new node and keep a reference
    auto node_ptr = std::make_unique<T>(this, std::forward<Args>(args)...);
    T* res = node_ptr.get();

    // move the unique_ptr into the vector
    m_children.push_back(std::move(node_ptr));

    // return a non owning pointer
    return res;
  }

  bool destroy_child(node_base* node);
};
} // namespace nn