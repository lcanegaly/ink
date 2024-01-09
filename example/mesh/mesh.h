#pragma once
#include <vector>
#include "../include/ink.h"

// Super basic screensaver example 
class MeshDemo : public Application {
 public:
  MeshDemo(const char* name, int width, int height); 
  void OnUserUpdate(std::time_t delta_t) override;
 private:
  PhysicsManager pm_; 
  void Load();
  Camera& camera_;
  Mesh* ram_;
  glm::vec2 mouse_pos_;
};

