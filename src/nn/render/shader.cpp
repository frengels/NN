#include "nn/render/shader.hpp"

#include <vector>

#include "nn/render/debug.hpp"

namespace nn {
shader::shader(GLenum type)
    : m_shader_id(glCreateShader(type))
    , m_type(type)
    , m_compiled(false) {
}

shader::~shader() {
  if (m_shader_id) {
    NN_GL_DEBUG(glDeleteShader(m_shader_id));
  }
}

GLuint shader::id() const {
  return m_shader_id;
}

bool shader::compile(const std::string& src) {
  if (m_compiled) {
    return false;
  }

  const char* src_cstr = src.c_str();
  const GLint length = src.size();
  NN_GL_DEBUG(glShaderSource(m_shader_id, 1, &src_cstr, &length));
  NN_GL_DEBUG(glCompileShader(m_shader_id));

  GLint status;
  NN_GL_DEBUG(glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &status));

  return m_compiled = status == GL_TRUE;
}

std::optional<std::string> shader::log() const {
  GLint length = 0;
  NN_GL_DEBUG(glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &length));

  if (length == 0) {
    return std::nullopt;
  }

  std::vector<GLchar> info_log(length);
  glGetShaderInfoLog(m_shader_id, std::size(info_log), &length,
                     std::data(info_log));

  return std::string(std::data(info_log));
}

bool shader::compiled() const {
  return m_compiled;
}

GLenum shader::type() const {
  return m_type;
}
} // namespace nn