#include "log/log.h"
#include <cmath>
#include <vector>
#include "renderer/renderer.h"
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>

const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 600;

void glfwErrorCallback(int error, const char* description);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main(void) {
  glfwInit();
  glfwSetErrorCallback(glfwErrorCallback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VOODOO FRIES", NULL, NULL);
  if (window == NULL) {
    Log::error("Failed to create a window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Log::error("GLAD initialization failed");
    glfwTerminate();
    return -1;
  }


  glClearColor(0.3f, 0.1f, 0.4f, 1.0f); // need to add glm

  std::vector<float> backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
  double delta = 0.0;
  double lastFrame = 0.0;

  while (!glfwWindowShouldClose(window)) {
    double currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;

    backgroundColor[0] = (sin(glfwGetTime())+ 1.0) / 2.0;
    backgroundColor[1] = (cos(glfwGetTime())+ 1.0) / 2.0;
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);


    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}

void glfwErrorCallback(int errorCode, const char *description) {
  std::stringstream ss;
  ss << errorCode << " - " << description;
  Log::error(ss.str());
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}