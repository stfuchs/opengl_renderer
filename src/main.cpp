#include <vector>

#include <opencv2/opencv.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "context.h"
#include "shader.h"
#include "object.h"

int main(int argc, char *argv[])
{
  const int w = 848;
  const int h = 480;
  // Set up windowless OpenGL context
  Context ctx(w, h);

  glEnable(GL_DEPTH_TEST);

  // Load and build shader
  Shader shader(
    "resources/shader/simple_vertex_shader.glsl",
    "resources/shader/simple_fragment_shader.glsl");

  const GLfloat vertices[] = {
    // position           // colors
     0.5f,  0.5f, 0.3f,   1.0f, 0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.3f,   0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.3f,   1.0f, 0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.3f,   0.0f, 1.0f, 0.0f, // top left
  };

  const GLuint indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  // Create vertices
  GLuint vbo, ebo, vao;
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenVertexArrays(1, &vao);

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // Render something
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw triangles
  shader.use();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  //eglSwapBuffers(eglDpy, eglSurf);

  cv::Mat image(cv::Size(w, h), CV_8UC3);
  glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, image.data);

  cv::imshow("Preview", image);
  cv::waitKey();

  cv::Mat depth(cv::Size(w, h), CV_32FC1);
  glReadPixels(0, 0, w, h, GL_DEPTH_COMPONENT, GL_FLOAT, depth.data);

  cv::imshow("Preview", depth);
  cv::waitKey();
  //cv::imwrite("image.png", image);


  return 0;

}
