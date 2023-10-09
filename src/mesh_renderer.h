#pragma once
#include "object.h"
class Mesh;
class MeshRenderer : public RenderDelegate {
 public: 
  MeshRenderer(Mesh& parent_mesh);
  void Draw() override; 
  void Load() override; 
 private:
  Mesh& mesh_;
  unsigned int vao_;
};
