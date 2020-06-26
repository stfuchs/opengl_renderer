#ifndef CONTEXT_H
#define CONTEXT_H

#include "core.h"

class Context
{
public:
  Context(int w, int h);
  ~Context();

  void init();

private:
  int w, h;
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
};

#endif
