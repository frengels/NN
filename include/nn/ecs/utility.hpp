#pragma once

#include <tuple>

namespace nn {
namespace detail {
template<typename... Args, typename Func, std::size_t... Idx>
void for_each_tuple_impl(const std::tuple<Args...>& t, Func&& f,
                         std::index_sequence<Idx...>) {
  (f(std::get<Idx>(t)), ...);
}
} // namespace detail

template<typename... Args, typename Func>
void for_each_tuple(const std::tuple<Args...>& t, Func&& f) {
  detail::for_each_tuple_impl(t, f, std::index_sequence_for<Args...>{});
}
} // namespace nn