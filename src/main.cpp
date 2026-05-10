#include "log/log.h"
#include "renderer/renderer.h"
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>

const int WINDOW_HEIGHT = 400;
const int WINDOW_WIDTH = 600;

void glfwErrorCallback(int error, const char* description);

int main(void)
{
  glfwSetErrorCallback(glfwErrorCallback);
}

void glfwErrorCallback(int errorCode, const char* description){
  std::stringstream ss;
  ss << errorCode << " - " << description;
  Log::error(ss.str());
}
