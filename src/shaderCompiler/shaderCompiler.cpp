#include <glad/glad.h>
#include <log/log.h>
#include "shaderCompiler.h"

unsigned int ShaderCompiler::createShaderProgram(std::string& ShaderSource){
  ParsedShader parsedShader = parseShader(ShaderSource);
  unsigned int fragmentShader = createShader(parsedShader.fragmentShader, GL_FRAGMENT_SHADER);
  unsigned int vertexShader   = createShader(parsedShader.vertexShader, GL_VERTEX_SHADER);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  return shaderProgram;
}

ParsedShader ShaderCompiler::parseShader(std::string_view shaderSource){

}

unsigned int ShaderCompiler::createShader(const char* parsedShaderSource, int shaderType){
  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &parsedShaderSource, NULL);
  glCompileShader(shader);

  int  shaderCompilationSuccess;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
  if(!shaderCompilationSuccess){
    Log::error("Shader compilation failed");
    Log::error(infoLog);
  }
  return shader;
}
