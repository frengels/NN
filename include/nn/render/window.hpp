#pragma once

#include <string>

#include <EGL/egl.h>

namespace nn {
class window {
private:
  EGLDisplay m_display;
  EGLConfig m_config;
  EGLContext m_context;
  EGLSurface m_surface;
  NativeWindowType m_native_window;
  EGLint m_num_config;

public:
  window(const std::string& name, size_t width, size_t height);
  ~window();
};
} // namespace nn