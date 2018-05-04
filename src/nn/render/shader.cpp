#include "nn/render/shader.hpp"

#include <fstream>
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

bool shader::compile_source(const std::string_view src) {
  if (m_compiled) {
    return false;
  }

  const char* src_cstr = std::data(src);
  const GLint length = std::size(src);
  NN_GL_DEBUG(glShaderSource(m_shader_id, 1, &src_cstr, &length));
  NN_GL_DEBUG(glCompileShader(m_shader_id));

  GLint status;
  NN_GL_DEBUG(glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &status));

  return m_compiled = status == GL_TRUE;
}

bool shader::compile_file(const std::string_view file) {
  if (m_compiled) {
    return false;
  }

  // attempt to open our file
  std::ifstream file_stream(std::data(file), std::ios::in | std::ios::ate);

  // check for bad bit
  if (file_stream.bad()) {
    return false;
  }

  auto end = file_stream.tellg();
  file_stream.seekg(0);

  // create buffer and read into it
  std::vector<char> src_buffer(end);
  file_stream.read(std::data(src_buffer), std::size(src_buffer));
  src_buffer.push_back('\0'); // add trailing null char

  file_stream.close();

  return compile_source(std::data(src_buffer));
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