#pragma once

#include <type_traits>

namespace nn {
template<typename T>
class movable_object_pool {
  static_assert(
      std::is_nothrow_move_constructible_v<T>,
      "T must be nothrow move constructible to make this pool efficient");

private:
  std::vector<T> m_objects;
  std::queue<size_t> m_free_objects;

public:
  movable_object_pool(size_t initial_size = 0)
      : m_objects(initial_size) {
    for (size_t i = 0; i < std::size(m_objects); ++i) {
      m_free_objects.push(i);
    }
  }

  T* acquire() {
    if (std::empty(m_free_objects)) {
      grow();
    }
    auto index = m_free_objects.front();
    m_free_objects.pop();

    return m_free_objects[index];
  }

  void release(T* object) {
    // acquire index of object
    size_t index = object - std::data(m_objects);
    assert(index < std::size(m_objects));

    m_free_objects.push(index);
  }

  void grow() {
    // grow by a factor of 2
    size_t old_size = std::size(m_objects);
    size_t new_size = 2 * old_size;
    m_objects.resize(new_size);

    for (size_t i = old_size; i < new_size; ++i) {
      m_free_objects.push(i);
    }
  }
};
} // namespace nn