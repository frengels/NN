#pragma once

namespace nn {
template <typename T> struct rectangle {
  T x;
  T y;

  T width;
  T height;

  rectangle(const T &x, const T &y, const T &width, const T &height)
      : x(x), y(y), width(width), height(height) {}
};
} // namespace nn