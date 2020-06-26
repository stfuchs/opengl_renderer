#include "context.h"

Context::Context(int w, int h) :
  w{w}, h{h}
{}

Context::~Context()
{
  if (context != EGL_NO_CONTEXT)
    eglDestroyContext(display, context);
  if (surface != EGL_NO_SURFACE)
    eglDestroySurface(display, surface);
  if (display != EGL_NO_DISPLAY)
    eglTerminate(display);
}

void Context::init()
{
  const EGLint configAttribs[] = {
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
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
    //EGL_CONTEXT_OPENGL_DEBUG, EGL_TRUE,
    EGL_NONE,
  };

  // Some advanced stuff:
  static const int MAX_DEVICES = 4;
  EGLDeviceEXT eglDevs[MAX_DEVICES];
  EGLint numDevices;
  PFNEGLQUERYDEVICESEXTPROC eglQueryDevicesEXT = (PFNEGLQUERYDEVICESEXTPROC) eglGetProcAddress("eglQueryDevicesEXT");
  eglQueryDevicesEXT(MAX_DEVICES, eglDevs, &numDevices);
  printf("Detected %d devices\n", numDevices);
  PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
    (PFNEGLGETPLATFORMDISPLAYEXTPROC) eglGetProcAddress("eglGetPlatformDisplayEXT");
  display = eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT, eglDevs[0], 0);

  // 1. Select display and initialize EGL
  //display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (display == EGL_NO_DISPLAY)
  {
    EGL_CHECK_ERR();
    throw std::runtime_error("EGL_NO_DISPLAY");
  }

  EGLint egl_major, egl_minor;
  if (!eglInitialize(display, &egl_major, &egl_minor))
  {
    EGL_CHECK_ERR();
  }
  std::cout << std::endl;
  std::cout << "EGL         : " << egl_major << "." << egl_minor << std::endl;
  std::cout << "EGL Client  : " << eglGetString_(display, EGL_CLIENT_APIS) << std::endl;
  std::cout << "EGL Ext     : " << eglGetString_(display, EGL_EXTENSIONS) << std::endl;
  std::cout << "EGL Vendor  : " << eglGetString_(display, EGL_VENDOR) << std::endl;

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;
  if (!eglChooseConfig(display, configAttribs, &eglCfg, 1, &numConfigs))
  {
    EGL_CHECK_ERR();
  }
  // 3. Create a rendering surface (we use pbuffer for off-screen)
  surface = eglCreatePbufferSurface(display, eglCfg, pbufferAttribs);
  if (surface == EGL_NO_SURFACE)
  {
    EGL_CHECK_ERR();
    throw std::runtime_error("EGL_NO_SURFACE");
  }

  // 4. Bind the API
  if (!eglBindAPI(EGL_OPENGL_API))
  {
    EGL_CHECK_ERR();
  }

  // 5. Create a context and make it current
  context = eglCreateContext(display, eglCfg, EGL_NO_CONTEXT, contextAttribs);
  if (context == EGL_NO_CONTEXT)
  {
    EGL_CHECK_ERR();
    throw std::runtime_error("EGL_NO_CONTEXT");
  }
  eglMakeCurrent(display, surface, surface, context);
  EGL_CHECK_ERR();

  // Start with GL specific setups
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    std::cout << "Debug context created." << std::endl;
    EGL_CHECK_ERR();
    GL_CHECK_ERR();
  }

  std::cout << std::endl;
  std::cout << "GL       : " << glGetString_(GL_VERSION) << std::endl;
  std::cout << "Vendor   : " << glGetString_(GL_VENDOR) << std::endl;
  std::cout << "Renderer : " << glGetString_(GL_RENDERER) << std::endl;

  glEnable(GL_DEPTH_TEST);
}
