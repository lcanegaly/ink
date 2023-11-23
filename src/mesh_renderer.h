#pragma once
#include "object.h"
#include "shader.h"

class Mesh;
class MeshRenderer : public RenderDelegate {
 public: 
  MeshRenderer(Mesh& parent_mesh, Shader* shader);
  void Draw() override; 
  void Load() override;
 private:
  Mesh& mesh_;
  Shader* shader_;
  unsigned int vao_;

};
