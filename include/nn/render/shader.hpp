#pragma once

#include <optional>
#include <string>

#include <GL/glew.h>

namespace nn {
class shader {
private:
  GLuint m_shader_id;
  GLenum m_type;
  bool m_compiled;

public:
  shader(GLenum type);
  ~shader();
  GLuint id() const;

  bool compile(const std::string& src);
  std::optional<std::string> log() const;

  bool compiled() const;

  GLenum type() const;
};
} // namespace nn