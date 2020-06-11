#include <iostream>

#include "context.h"


Context::Context(int w, int h)
{
  const EGLint configAttribs[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_NONE
  };

  const EGLint pbufferAttribs[] = {
    EGL_WIDTH, w,
    EGL_HEIGHT, h,
    EGL_NONE,
  };

  const EGLint contextAttribs[] = {
    EGL_CONTEXT_MAJOR_VERSION, 3,
    EGL_CONTEXT_MINOR_VERSION, 3,
    EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
    EGL_NONE,
  };

  // 1. Initialize EGL
  display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  //EGLDisplay display = eglGetPlatformDisplay
  EGLint major, minor;
  eglInitialize(display, &major, &minor);
  std::cout << "EGL: " << major << "." << minor << std::endl;

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;
  eglChooseConfig(display, configAttribs, &eglCfg, 1, &numConfigs);

  // 3. Create a surface
  EGLSurface eglSurf = eglCreatePbufferSurface(display, eglCfg, pbufferAttribs);

  // 4. Bind the API
  eglBindAPI(EGL_OPENGL_API);

  // 5. Create a context and make it current
  EGLContext eglCtx = eglCreateContext(display, eglCfg, EGL_NO_CONTEXT, contextAttribs);
  eglMakeCurrent(display, eglSurf, eglSurf, eglCtx);
}

Context::~Context()
{
  eglTerminate(display);
}
