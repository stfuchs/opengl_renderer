#include "context.h"
#include "mesh.h"
#include "objects.hpp"
#include "shader.h"
#include "image.h"

int main(int argc, char *argv[])
{
  const int w = 848;
  const int h = 480;

  // Set up windowless OpenGL context
  Context ctx(w, h);
  ctx.init();

  // Load and build shader
  Shader shader(
    "resources/shader/simple_vertex_shader.glsl",
    "resources/shader/simple_fragment_shader.glsl");

  auto tex_container = Image::load("resources/texture/container.jpg");

  auto mesh = Square();

  // Render something
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mesh.draw(shader);

  auto image = Image::create(w, h, 3);
  glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image->data);
  Image::save("gl_color.png", image);

  return 0;
}
