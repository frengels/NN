#include "nn/render/debug.hpp"

#include <cstdio>
#include <string>

#include <GL/glew.h>

namespace nn {
void _gl_check_error(const char* file, int line, const char* expression) {
  GLenum error_code = glGetError();

  if (error_code == GL_NO_ERROR) {
    return;
  }

  std::string error_msg;

  switch (error_code) {
  case GL_INVALID_ENUM:
    error_msg = "GL_INVALID_ENUM";
    break;
  case GL_INVALID_VALUE:
    error_msg = "GL_INVALID_VALUE";
    break;
  case GL_INVALID_OPERATION:
    error_msg = "GL_INVALID_OPERATION";
    break;
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    error_msg = "GL_INVALID_FRAMEBUFFER_OPERATION";
    break;
  case GL_OUT_OF_MEMORY:
    error_msg = "GL_OUT_OF_MEMORY";
    break;
  case GL_STACK_UNDERFLOW:
    error_msg = "GL_STACK_UNDERFLOW";
    break;
  case GL_STACK_OVERFLOW:
    error_msg = "GL_STACK_OVERFLOW";
    break;
  default:
    error_msg = "GL_UNKNOWN_ERROR";
    break;
  }

  fprintf(stderr, "%s:%d OpenGL: %s in %s\n", file, line, error_msg.c_str(),
          expression);
}
} // namespace nn