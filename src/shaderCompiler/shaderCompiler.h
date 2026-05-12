#pragma once

#include <string>

struct ParsedShader{
  std::string vertexSource;
  std::string fragmentSource;
};

class ShaderCompiler{
public:
  static unsigned int createShaderProgram(std::string shaderFilePath);
private:
  static ParsedShader parseShader(std::string& shaderFilePath);
  static unsigned int createShader(const char* parsedShaderSource, int shaderType);
};