#pragma once
#include "object.h"
#include "transform.h"
#include "renderer.h"

class NodeUpdate : public UpdateDelegate {
 public: 
  NodeUpdate(Object& parent) : parent_{parent}{
     
  }
  void Update(std::time_t delta_t) override {
     
  }
 private:
  Object& parent_;
};

class Mesh : public RenderDelegate {
 public: 
  void Draw() override {
    Transform2D transform; 
    Renderer::Get().LoadShader();
    rotate += 0.1;
    transform.x.x = rotate;
    Renderer::Get().Draw(transform); 
  }
  void Load() override {}
  void Load(const char* filepath) override {}
  private:
    double rotate = 0.0;
};

class Node2D : public Object {
 public:
  Node2D() : Object(new NodeUpdate(*this), new Mesh){
  } 
   Transform2D transform;
  
};
