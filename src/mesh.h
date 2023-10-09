#pragma once
#include "object.h"
#include "mesh_renderer.h"
#include "glm.hpp"

struct Vertex{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
};

class Mesh : public Object {
 public:
  Mesh():Object(new NoUpdate, new MeshRenderer(*this)){
  }
 private:
  std::vector<Vertex> vertices;
};



