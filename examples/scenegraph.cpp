#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nn/render/2d/renderer2d.hpp"
#include "nn/render/2d/sprite.hpp"
#include "nn/render/shader_program.hpp"

nn::shader_program load_shaders() {
  nn::shader vert_shader(GL_VERTEX_SHADER);
  if (!vert_shader.compile_file("examples/shaders/basic.vert")) {
    printf(vert_shader.log()->c_str());
  }
  nn::shader frag_shader(GL_FRAGMENT_SHADER);
  if (!frag_shader.compile_file("examples/shaders/basic.frag")) {
    printf(frag_shader.log()->c_str());
  }

  nn::shader_program prog;
  prog.attach(vert_shader);
  prog.attach(frag_shader);

  if (!prog.link()) {
    printf(prog.log()->c_str());
  }

  if (!prog.valid()) {
    printf(prog.log()->c_str());
  }

  return prog;
}

int main(void) {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(800, 800, "Sprite", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = true;
  // after window because we need an opengl context first
  glewInit();

  nn::shader_program prog = load_shaders();

  auto cat2_tex = std::make_shared<nn::texture>("examples/textures/cat2.jpg");
  nn::sprite cat2_sprite(cat2_tex);

  auto cat_tex = std::make_shared<nn::texture>("examples/textures/cat.png");
  nn::sprite cat_sprite(cat_tex);

  nn::renderer2d sprite_renderer;
}