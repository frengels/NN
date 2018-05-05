#pragma once

#include <type_traits>

namespace nn {
template<typename V>
struct is_vertex : public std::false_type {};
} // namespace nn