#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Renderer{

public:
  void init();
  void createWindow();
  void run();
  void terminate();

private:
  static void framebufferSizeCallback(GLFWwindow* window, int width, int height); // fix static methods
  static void glfwErrorCallback(int error, const char* description);

public:
  double delta {0.0};
  int windowWidth {600};
  int windowHeight {400};
  const char* windowName = "VOODOO FRIES";

private:
  GLFWwindow* window;
};