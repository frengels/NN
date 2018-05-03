#pragma once

#include <string>

namespace nn {
class window {
  window(const std::string& name, size_t width, size_t height);
  ~window();
};
} // namespace nn