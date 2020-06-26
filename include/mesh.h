#ifndef MESH_H
#define MESH_H

#include "core.h"
#include "shader.h"

struct Vertex
{
  glm::vec3 position;
  //glm::vec3 normal;
  glm::vec3 color;
};

struct Texture
{
  unsigned int id;
  std::string type;
};

class Mesh
{
public:
  // mesh data
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  //std::vector<Texture> textures;

  /// Constructor
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

  void draw(Shader& shader);

private:
  // render data
  unsigned int VAO, VBO, EBO;

  void setupMesh();
};

#endif
