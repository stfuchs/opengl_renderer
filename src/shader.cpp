#include "shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  auto _read = [](const auto& path) -> std::string {
    std::stringstream stream;
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
      file.open(path);
      stream << file.rdbuf();
      file.close();
    }
    catch (const std::ifstream::failure& ex)
    {
      std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << path << std::endl;
    }
    return stream.str();
  };

  auto vShaderCodeStr = _read(vertexPath);
  auto fShaderCodeStr = _read(fragmentPath);
  const char* vShaderCode = vShaderCodeStr.c_str();
  const char* fShaderCode = fShaderCodeStr.c_str();

  GLint success;
  GLchar infoLog[512];

  auto _checkShader = [&success, &infoLog](GLuint shader) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
  };

  auto _checkProgram = [&success, &infoLog](GLuint program) {
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
  };

  std::cout <<
    "Creating vertex shader:\n" <<
    "---------------------------------------------------------------------------\n" <<
    vShaderCode <<
    "---------------------------------------------------------------------------\n" << std::endl;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCode, NULL);
  glCompileShader(vertexShader);
  _checkShader(vertexShader);

  std::cout <<
    "Creating fragment shader:\n" <<
    "---------------------------------------------------------------------------\n" <<
    fShaderCode <<
    "---------------------------------------------------------------------------\n" << std::endl;
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
  glCompileShader(fragmentShader);
  _checkShader(fragmentShader);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  _checkProgram(ID);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
}

void Shader::setInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
