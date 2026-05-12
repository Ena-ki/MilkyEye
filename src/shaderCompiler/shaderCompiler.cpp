#include <cstdio>
#include <glad/glad.h>
#include <log/log.h>
#include "shaderCompiler.h"
#include <fstream>
#include <sstream>

unsigned int ShaderCompiler::createShaderProgram(std::string shaderFilePath){
  ParsedShader parsedShader = parseShader(shaderFilePath);
  unsigned int fragmentShader = createShader(parsedShader.fragmentSource.c_str(), GL_FRAGMENT_SHADER);
  unsigned int vertexShader   = createShader(parsedShader.vertexSource.c_str(), GL_VERTEX_SHADER);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  return shaderProgram;
}

ParsedShader ShaderCompiler::parseShader(std::string& shaderFilePath){
  enum class ShaderType{
    NONE = -1,
    FRAGMENT = 0,
    VERTEX = 1
  };
  std::ifstream shaderFile(shaderFilePath);
  
  ParsedShader result;
  std::stringstream vertexSS ;
  std::stringstream fragmentSS ;
  ShaderType currentShaderType = ShaderType::NONE;

  std::string line = "";
  while(getline(shaderFile, line))
  {
    if(line.find("#shader") != std::string::npos){
      if(line.find("vertex") != std::string::npos){
        currentShaderType = ShaderType::VERTEX;
      }
      if(line.find("fragment") != std::string::npos){
        currentShaderType = ShaderType::FRAGMENT;
      }
      continue;
    }

    switch (currentShaderType) {
      case ShaderType::FRAGMENT:
        fragmentSS << line << '\n';
        break;
      case ShaderType::VERTEX:
        vertexSS << line << '\n';
        break;
      case ShaderType::NONE:
        Log::error("Shader type declaration must be in front of the code");
        return result;
    }
  }
  result.fragmentSource = fragmentSS.str();
  result.vertexSource = vertexSS.str();
  return result;
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
