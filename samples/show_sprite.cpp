#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nn/2d/sprite.hpp"
#include "nn/2d/sprite_batch.hpp"

int main(int argc, char** argv) {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(800, 800, "Sprite", nullptr, nullptr);
  glewExperimental = true;
  // after window because we need an opengl context first
  glewInit();

  nn::image cat_image("textures/cat.png", nn::image::channels::RGBA);
  auto cat_tex =
      std::make_shared<nn::texture>(cat_image, nn::texture::wrap::REPEAT);
  nn::sprite cat_sprite(cat_tex);

  nn::sprite_batch cat_batch;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    cat_batch.add(cat_sprite, glm::mat4());
    cat_batch.flush();
  }
}