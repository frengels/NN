#pragma once

#define NN_GL_DEBUG(expr)                                                      \
  (expr);                                                                      \
  nn::_gl_check_error(__FILE__, __LINE__, #expr)

namespace nn {
void _gl_check_error(const char* file, int line, const char* expression);
}