#ifndef SHADER_H
#define SHADER_H

#include "core.h"

class Shader
{
public:
  /// Constructor reads and builds shader
  Shader(const std::string& vertexPath, const std::string& fragmentPath);

  /// use/activate the shader
  void use();
  /// utility uniform function for bool
  void setBool(const std::string& name, bool value) const;
  /// utility uniform function for int
  void setInt(const std::string& name, int value) const;
  /// utility uniform function for float
  void setFloat(const std::string& name, float value) const;
private:
  /// program ID
  GLuint ID;

};

#endif
