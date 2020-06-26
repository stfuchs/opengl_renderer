#ifndef CORE_H
#define CORE_H

// Standard
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// opencv
#ifdef HAVE_OPENCV
#include <opencv2/opencv.hpp>
#endif

// OpenGL
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/egl.h>
#include <EGL/eglext.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>

// glm
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void eglCheckError_(const char *file, int line);
#define EGL_CHECK_ERR() eglCheckError_(__FILE__, __LINE__)

void glCheckError_(const char *file, int line);
#define GL_CHECK_ERR() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(
  GLenum source,
  GLenum type,
  unsigned int id,
  GLenum severity,
  GLsizei length,
  const char *message,
  const void *userParam);

inline std::string glGetString_(const GLint name)
{
  return std::string{reinterpret_cast<const char*>(glGetString(name))};
}

inline std::string eglGetString_(const EGLDisplay dpy, const EGLint name)
{
  return std::string{reinterpret_cast<const char*>(eglQueryString(dpy, name))};
}

#endif
