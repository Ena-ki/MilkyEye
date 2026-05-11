#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer/renderer.h"


int main(void) {
  Renderer renderer;
  renderer.init();
  renderer.createWindow();
  renderer.run();
  renderer.terminate();
}