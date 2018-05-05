#pragma once

namespace nn {
template<typename T>
struct clip {
  T x;
  T y;

  T width;
  T height;

  clip(const T& x, const T& y, const T& width, const T& height)
      : x(x)
      , y(y)
      , width(width)
      , height(height) {
  }
};

typedef clip<size_t> stclip;
typedef clip<uint64_t> ui64clip;
typedef clip<uint32_t> ui32clip;
typedef clip<uint16_t> ui16clip;
typedef clip<uint8_t> ui8clip;
} // namespace nn