#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

// the big idea is that:
//  Renderer will be an object, which I don't like, but whatever I guess.
//  It will return a window when you create a window.
//  and then it will be immutable so that when you call start application,
//  it starts with the window
//
//  You might say that it is dumb to have it in the same class.
//  I say yes
//  but I don't have much time

class Renderer
{
  public:

  Renderer();
  ~Renderer();

  void applicationLoop(GLFWwindow* window);
  GLFWwindow* createApplicationWindow(unsigned int windowWidth, unsigned int windowHeight);

  private:

  void processInput(GLFWwindow* window);
  void initializeGLAD();
  static void framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight);

};
