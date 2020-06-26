#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "mesh.h"

class Square : public Mesh
{
public:
  Square() :
    Mesh{{
      {{ 0.5f,  0.5f, 0.3f}, {1.0f, 0.0f, 0.0f}}, // top right
      {{ 0.5f, -0.5f, 0.3f}, {0.0f, 1.0f, 0.0f}}, // bottom right
      {{-0.5f, -0.5f, 0.3f}, {1.0f, 0.0f, 0.0f}}, // bottom left
      {{-0.5f,  0.5f, 0.3f}, {0.0f, 1.0f, 0.0f}}}, // top left
    {0, 1, 3, 1, 2, 3}}
  { }
};

#endif
