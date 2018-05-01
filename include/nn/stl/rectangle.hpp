#pragma once

namespace nn {
template<typename T>
struct rectangle {
  T x;
  T y;

  T width;
  T height;

  rectangle(const T& x, const T& y, const T& width, const T& height)
      : x(x)
      , y(y)
      , width(width)
      , height(height) {
  }
};

typedef rectangle<size_t> srectangle;
typedef rectangle<uint64_t> ui64rectangle;
typedef rectangle<uint32_t> ui32rectangle;
typedef rectangle<uint16_t> ui16rectangle;
typedef rectangle<uint8_t> ui8rectangle;
} // namespace nn