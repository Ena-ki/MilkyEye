#include "process.h"

void applicationLoop(GLFWwindow* window)
{
  while(!glfwWindowShouldClose(window)){
    glfwSwapBuffers(window);
    processInput(window);
    glfwPollEvents();


  }
  glfwTerminate();
}


void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, true);
}
