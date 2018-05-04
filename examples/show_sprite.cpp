#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

#include "nn/fs/fs_monitor.hpp"
#include "nn/render/2d/sprite.hpp"
#include "nn/render/2d/sprite_batch.hpp"
#include "nn/render/debug.hpp"
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

int main(int argc, char** argv) {
  char buffer[FILENAME_MAX];
  getcwd(buffer, FILENAME_MAX);

  glfwInit();
  GLFWwindow* window = glfwCreateWindow(800, 800, "Sprite", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = true;
  // after window because we need an opengl context first
  glewInit();

  nn::shader_program prog = load_shaders();

  nn::fs_monitor shader_watch;

  shader_watch.watch("examples/shaders/basic.vert");
  shader_watch.watch("examples/shaders/basic.frag");

  shader_watch.run();

  nn::image cat_image;
  assert(
      cat_image.load("examples/textures/cat.png", nn::image::channels::RGBA));
  auto cat_tex =
      std::make_shared<nn::texture>(cat_image, nn::texture::wrap::REPEAT);
  nn::sprite cat_sprite(cat_tex);

  nn::sprite_batch cat_batch;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window)) {
    NN_GL_DEBUG(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                        GL_STENCIL_BUFFER_BIT));
    glfwPollEvents();

    nn::fs_event fs_event;
    while (shader_watch.poll_events(fs_event)) {
      if (fs_event.mask & IN_MODIFY) {
        prog = load_shaders();
      }
    }

    prog.bind();
    auto scale =
        glm::scale(glm::vec3(0.002f, 0.002f, 0.002f)); // make cat fit on screen

    cat_batch.add(cat_sprite, glm::mat4());
    cat_batch.add(cat_sprite, glm::translate(glm::vec3(100.f, 0.f, 0.f)));
    cat_batch.flush(prog, scale);

    glfwSwapBuffers(window);
  }

  shader_watch.stop();
}