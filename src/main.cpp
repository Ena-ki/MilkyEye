#include "./process.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

void configureApplicationWindow();
GLFWwindow* createApplicationWindow(uint windowWidth, uint windowHeight);
void initializeGLAD();
void framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight);

const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 600;

int main(void)
{
  glfwInit();
  configureApplicationWindow();

  GLFWwindow* window = createApplicationWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
  applicationLoop(window);
}




void configureApplicationWindow()
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


GLFWwindow* createApplicationWindow(uint windowWidth, uint windowHeight)
{
  GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Milky Eye", NULL, NULL);
  if(window == NULL){
    glfwTerminate();
    throw std::runtime_error("Failed to create a window");
  }
  glfwMakeContextCurrent(window);
  initializeGLAD();

  glViewport(0, 0, windowWidth, windowHeight);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  return window;
} 


void initializeGLAD()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }
}


void framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight)
{
  glViewport(0, 0, windowWidth, windowHeight);
}
