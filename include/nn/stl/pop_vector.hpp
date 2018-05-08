#pragma once

#include <vector>

namespace nn {
template<typename T>
class pop_vector : public std::vector<T> {
public:
  using parent_type = std::vector<T>;
  using parent_type::emplace_back;
  using parent_type::iterator;
  using parent_type::parent_type;
  using parent_type::push_back;

public:
  /**
   * returns the iterator to the element swapped to the current position
   */
  iterator erase(iterator position) {
    swap(position, std::end(*this));
    pop_back();
    return position;
  }
};
} // namespace nn