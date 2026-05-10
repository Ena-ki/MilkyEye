#include "renderer.h"
#include "GLFW/glfw3.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::applicationLoop(GLFWwindow* window)
{
  while(!glfwWindowShouldClose(window)){
    glClearColor(0.4f, 0.3f, 0.5f, 1.0f);
    processInput(window);

    // rendering

    glClear(GL_COLOR_BUFFER_BIT);


    // buffer swap has to be last
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
}


void Renderer::processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, true);

  //remove after
  if(glfwGetKey(window, GLFW_KEY_1))
    glClearColor(0.3f, 0.1f, 0.4f, 1.0f);
}


GLFWwindow* Renderer::createApplicationWindow(unsigned int windowWidth, unsigned int windowHeight)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Milky Eye", NULL, NULL);
  if(window == NULL){
    glfwTerminate();
    throw std::runtime_error("Failed to create a window");
  }
  glfwMakeContextCurrent(window);
  initializeGLAD();

  glViewport(0, 0, windowWidth, windowHeight);
  glfwSetFramebufferSizeCallback(window, Renderer::framebuffer_size_callback);
  return window;
} 


void Renderer::initializeGLAD()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize GLAD");
  }
}


void Renderer::framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight)
{
  glViewport(0, 0, windowWidth, windowHeight);
}
