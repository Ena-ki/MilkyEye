#pragma once

#include <string>
#include <utility>

struct ParsedShader{
  const char* vertexShader;
  const char* fragmentShader;
};

class ShaderCompiler{
public:
  unsigned int createShaderProgram(std::string& ShaderSource);
private:
  ParsedShader parseShader(std::string_view shaderSource);
  unsigned int createShader(const char* parsedShaderSource, int shaderType);
};