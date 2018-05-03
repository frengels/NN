#include "nn/render/window.hpp"

#include <cassert>

#include <EGL/egl.h>

namespace nn {
window::window(const std::string& name, size_t width, size_t height) {
  EGLint attribute_list[]{EGL_RED_SIZE,
                          8,
                          EGL_GREEN_SIZE,
                          8,
                          EGL_BLUE_SIZE,
                          8,
                          EGL_ALPHA_SIZE,
                          8,
                          EGL_COLOR_BUFFER_TYPE,
                          EGL_RGB_BUFFER,
                          EGL_CONFORMANT,
                          EGL_OPENGL_ES3_BIT,
                          EGL_NONE};

  EGLint context_attributes[]{EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
  m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  assert(eglInitialize(m_display, nullptr, nullptr));
  assert(
      eglChooseConfig(m_display, attribute_list, &m_config, 1, &m_num_config));
  m_context =
      eglCreateContext(m_display, m_config, EGL_NO_CONTEXT, context_attributes);
  // TODO: m_native_window
  m_surface =
      eglCreateWindowSurface(m_display, m_config, m_native_window, nullptr);
  eglMakeCurrent(m_display, m_surface, m_surface, m_context);
}
} // namespace nn