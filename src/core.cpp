#include "core.h"

void eglCheckError_(const char *file, int line)
{
  EGLint errorCode;
  bool shallThrow = false;
  while ((errorCode = eglGetError()) != EGL_SUCCESS)
  {
    std::string msg;
    switch (errorCode)
    {
    case EGL_NOT_INITIALIZED:
      msg = "EGL_NOT_INITIALIZED: "
        "EGL is not initialized, or could not be initialized, for the specified EGL display connection.";
      break;
    case EGL_BAD_ACCESS:
      msg = "EGL_BAD_ACCESS: "
        "EGL cannot access a requested resource (for example a context is bound in another thread).";
      break;
    case EGL_BAD_ALLOC:
      msg = "EGL_BAD_ALLOC: "
        "EGL failed to allocate resources for the requested operation.";
      break;
    case EGL_BAD_ATTRIBUTE:
      msg = "EGL_BAD_ATTRIBUTE: "
        "An unrecognized attribute or attribute value was passed in the attribute list.";
      break;
    case EGL_BAD_CONTEXT:
      msg = "EGL_BAD_CONTEXT: "
        "An EGLContext argument does not name a valid EGL rendering context.";
      break;
    case EGL_BAD_CONFIG:
      msg = "EGL_BAD_CONFIG: "
        "An EGLConfig argument does not name a valid EGL frame buffer configuration.";
      break;
    case EGL_BAD_CURRENT_SURFACE:
      msg = "EGL_BAD_CURRENT_SURFACE: "
        "The current surface of the calling thread is a window, pixel buffer or pixmap that is no longer valid.";
      break;
    case EGL_BAD_DISPLAY:
      msg = "EGL_BAD_DISPLAY: "
        "An EGLDisplay argument does not name a valid EGL display connection.";
      break;
    case EGL_BAD_SURFACE:
      msg = "EGL_BAD_SURFACE: "
        "An EGLSurface argument does not name a valid surface (window, pixel buffer or pixmap) configured for "
        "GL rendering.";
      break;
    case EGL_BAD_MATCH:
      msg = "EGL_BAD_MATCH: "
        "Arguments are inconsistent (for example, a valid context requires buffers not supplied by a valid surface).";
      break;
    case EGL_BAD_PARAMETER:
      msg = "EGL_BAD_PARAMETER: "
        "One or more argument values are invalid.";
      break;
    case EGL_BAD_NATIVE_PIXMAP:
      msg = "EGL_BAD_NATIVE_PIXMAP: "
        "A NativePixmapType argument does not refer to a valid native pixmap.";
      break;
    case EGL_BAD_NATIVE_WINDOW:
      msg = "EGL_BAD_NATIVE_WINDOW: "
        "A NativeWindowType argument does not refer to a valid native window.";
      break;
    case EGL_CONTEXT_LOST:
      msg = "EGL_CONTEXT_LOST: "
        "A power management event has occurred. The application must destroy all contexts "
        "and reinitialise OpenGL ES state and objects to continue rendering.";
      break;
    }
    std::cout << msg << " | " << file << " (" << line << ")" << std::endl;
    shallThrow = true;
  }
  if (shallThrow)
    throw std::runtime_error("EGL Error");
}

void glCheckError_(const char *file, int line)
{
  GLenum errorCode;
  bool shallThrow = false;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string error;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
    case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
    case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    shallThrow = true;
  }
  if (shallThrow)
    throw std::runtime_error("GL Error");
}

void APIENTRY glDebugOutput(
  GLenum source,
  GLenum type,
  unsigned int id,
  GLenum severity,
  GLsizei length,
  const char *message,
  const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}
