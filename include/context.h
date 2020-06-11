#ifndef CONTEXT_H
#define CONTEXT_H


#include <EGL/egl.h>

class Context
{
public:
  Context(int w, int h);
  ~Context();

private:
  EGLDisplay display;
};

#endif
