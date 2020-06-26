#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
  vertices{vertices},
  indices{indices}
{
  setupMesh();
}

void Mesh::setupMesh()
{
  // Create vertices
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);
  GL_CHECK_ERR();

  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
  GL_CHECK_ERR();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
  GL_CHECK_ERR();

  // vertex positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);
  GL_CHECK_ERR();

  // vertex colors
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
  glEnableVertexAttribArray(1);
  GL_CHECK_ERR();

  // vertex normals
  //glEnableVertexAttribArray(2);
  //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(offsetof(Vertex, normal)));

  glBindVertexArray(0);
}

void Mesh::draw(Shader& shader)
{
  // Draw triangles
  shader.use();

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
