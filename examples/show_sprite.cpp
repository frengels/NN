#include <fstream>
#include <iostream>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>

#if defined(__linux__)
#include "nn/fs/fs_monitor.hpp"
#include <unistd.h>
#endif
#include "nn/ecs/entity_handle.hpp"
#include "nn/ecs/systems/renderable2d_system.hpp"
#include "nn/ecs/systems/transform2d_system.hpp"
#include "nn/render/2d/renderer2d.hpp"
#include "nn/render/2d/sprite.hpp"
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

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(800, 800, "Sprite", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewExperimental = true;
  // after window because we need an opengl context first
  glewInit();

  nn::entity_manager<nn::transform2d_component, nn::sprite_component> manager;

  auto cat1 = nn::make_entity_unique(manager);
  auto cat2 = nn::make_entity_unique(manager);

  manager.attach_emplace<nn::transform2d_component>(
      cat1->entity(), glm::vec2(-300.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, 0,
      0.0f);

  manager.attach_emplace<nn::transform2d_component>(
      cat2->entity(), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, -1,
      0.1f);

  nn::shader_program prog = load_shaders();

#if defined(__linux__)
  nn::fs_monitor shader_watch;
  shader_watch.watch("examples/shaders/basic.vert");
  shader_watch.watch("examples/shaders/basic.frag");

  shader_watch.run();
#endif

  auto cat2_tex = std::make_shared<nn::texture>("examples/textures/cat2.jpg");
  auto cat_tex = std::make_shared<nn::texture>("examples/textures/cat.png");

  manager.attach_emplace<nn::sprite_component>(cat1->entity(), true, cat_tex);
  manager.attach_emplace<nn::sprite_component>(cat2->entity(), true, cat2_tex);

  nn::renderer_system<decltype(manager)> render_system(manager);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  while (!glfwWindowShouldClose(window)) {
    NN_GL_DEBUG(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
                        GL_STENCIL_BUFFER_BIT));
    glfwPollEvents();

#if defined(__linux__)
    nn::fs_event fs_event;
    while (shader_watch.poll_events(fs_event)) {
      if (fs_event.mask & IN_MODIFY) {
        prog = load_shaders();
      }
    }
#endif

    prog.bind();
    auto scale =
        glm::scale(glm::vec3(0.002f, 0.002f, 0.002f)); // make cat fit on screen

    prog.bind();
    prog.uniform(nn::shader_program::MVP_LOCATION, scale);

    render_system(manager, 0.0f);

    glfwSwapBuffers(window);
  }
#if defined(__linux__)
  shader_watch.stop();
#endif
}