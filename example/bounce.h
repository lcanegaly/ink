#pragma once
#include <vector>
#include "../include/ink.h"

// Super basic screensaver example 
class Bounce: public Application {
 public:
  Bounce(const char* name, int width, int height); 
  void OnUserUpdate() override;
 private:
  void Load(); 
};

// Ball class had an ImageView child node.
class Ball : public Object {
 public:
   Ball();
 private:
  void OnUserUpdate(time_t delta_t) override; 
  Vec2 velocity_ {0.01, 0.01};
};

