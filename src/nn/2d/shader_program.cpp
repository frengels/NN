#include "nn/2d/shader_program.hpp"

#include <memory>

#include "nn/2d/debug.hpp"

namespace nn {
shader_program::shader_program()
    : m_program_id(glCreateProgram())
    , m_linked(false) {
}

shader_program::~shader_program() {
  if (m_program_id) {
    glDeleteShader(m_program_id);
  }
}

bool shader_program::attach(const shader& s) {
  if (m_linked) {
    return false;
  }

  NN_GL_DEBUG(glAttachShader(m_program_id, s.id()));
  m_unlinked_shaders.push_back(s.id());

  return true;
}

bool shader_program::link() {
  NN_GL_DEBUG(glLinkProgram(m_program_id));

  GLint status;
  glGetProgramiv(m_program_id, GL_LINK_STATUS, &status);

  // shaders were linked so detach them
  for (const auto& shader : m_unlinked_shaders) {
    NN_GL_DEBUG(glDetachShader(m_program_id, shader));
  }
  // clear and shrink vector
  m_unlinked_shaders.clear();
  m_unlinked_shaders.shrink_to_fit();

  // verify compilation succeeded
  return m_linked = status == GL_TRUE;
}

bool shader_program::valid() const {
  glValidateProgram(m_program_id);

  GLint status;
  glGetProgramiv(m_program_id, GL_VALIDATE_STATUS, &status);

  return status == GL_TRUE;
}

bool shader_program::is_linked() const {
  return m_linked;
}

void shader_program::bind() const {
  NN_GL_DEBUG(glUseProgram(m_program_id));
}
void shader_program::unbind() const {
  NN_GL_DEBUG(glUseProgram(0));
}

void shader_program::uniform(GLint location, const glm::mat4& m,
                             bool transpose) {
  NN_GL_DEBUG(glUniformMatrix4fv(location, 1, transpose, &m[0][0]));
}

void shader_program::uniform(GLint location, GLint i) {
  NN_GL_DEBUG(glUniform1i(location, i));
}

bool shader_program::bind_attribute_location(const std::string& attr,
                                             GLint location) const {
  if (m_linked) {
    return false;
  }

  NN_GL_DEBUG(glBindAttribLocation(m_program_id, location, attr.c_str()));
  return false;
}

GLint shader_program::uniform_location(const std::string& uniform) const {
  return glGetUniformLocation(m_program_id, uniform.c_str());
}
GLint shader_program::attribute_location(const std::string& attr) const {
  return glGetAttribLocation(m_program_id, attr.c_str());
}

std::optional<std::string> shader_program::log() const {
  GLint length = 0;
  glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &length);

  if (length == 0) {
    return std::nullopt;
  }

  std::vector<GLchar> info_log(length);
  glGetProgramInfoLog(m_program_id, std::size(info_log), &length,
                      std::data(info_log));

  return std::string(std::data(info_log));
}
} // namespace nn