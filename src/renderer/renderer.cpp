#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include <sstream>
#include "log/log.h"

void Renderer::glfwErrorCallback(int errorCode, const char *description) {
  std::stringstream ss;
  ss << errorCode << " - " << description;
  Log::error(ss.str());
}


void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}


void Renderer::init(){
  glfwInit();
  glfwSetErrorCallback(Renderer::glfwErrorCallback);
}


void Renderer::createWindow(){
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);

  if (window == NULL) {
    Log::error("Failed to create a window");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // fix this

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Log::error("GLAD initialization failed"); // this needs to throw an exception
    glfwTerminate();
    return;
  }
}

void Renderer::run(){
  delta = 0.0;
  double lastFrame = 0.0;
  double currentFrame = 0.0;

  while (!glfwWindowShouldClose(window)) {
    currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}


void Renderer::terminate(){
  if(window)
    glfwDestroyWindow(window);
  glfwTerminate();
}