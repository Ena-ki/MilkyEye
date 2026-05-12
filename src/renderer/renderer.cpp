#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include <sstream>
#include "log/log.h"
#include <cmath>


void Renderer::init(){
  glfwInit();
  glfwSetErrorCallback(Renderer::glfwErrorCallback);
}


void Renderer::createWindow(){
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  
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

  int viewportWidth;
  int viewportHeight;
  glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
  glViewport(0, 0, viewportWidth, viewportHeight);

  GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
  glfwSetCursor(window, cursor);
}


void Renderer::run(){

  delta = 0.0;
  double lastFrame = 0.0;
  double currentFrame = 0.0;


  const char *vertexShaderSource ="#version 430 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
  
 const char *fragmentShaderSource = "#version 430 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

  float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };


  
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  int  shaderCompilationSuccess;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
  if(!shaderCompilationSuccess){
    Log::error("Shader compilation failed");
    Log::error(infoLog);
  }
  
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); // WHAT?

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
                                                                                             
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    
    currentFrame = glfwGetTime();
    delta = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.4f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}


void Renderer::terminate(){
  if(window)
    glfwDestroyWindow(window);
  glfwTerminate();
}


void Renderer::glfwErrorCallback(int errorCode, const char *description) {
  std::stringstream ss;
  ss << errorCode << " - " << description;
  Log::error(ss.str());
}


void Renderer::framebufferSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}