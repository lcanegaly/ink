#pragma once
#include <vector>
#include "../include/ink.h"

// Super basic screensaver example 
class Merge: public Application {
 public:
  Merge(const char* name, int width, int height); 
  void OnUserUpdate(std::time_t delta_t) override;
 private:
  void Load();
  Camera camera_;
  glm::vec2 mouse_pos_;
};

// Ball class had an ImageView child node.
class Ball : public Object {
 public: 
   Ball();
 private:
  void OnUserUpdate(time_t delta_t) override; 
  Vec2 velocity_ {0.01, 0.01};
};

