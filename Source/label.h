#pragma once
#include "renderer.h"
#include "sprite.h"
#include "object.h"
#include "textbox.h"
#include <unordered_map>
#include <string>
#include "glm.hpp"

class Label : public Object {
 public:
  Label(const char* filepath, int size, int X, int Y);
  void SetupFont();
  void Update()override; 
  void SetText(const std::string text);
  void SetUpdateFrequency(int ticks_per_update) {ticks_per_update_ = ticks_per_update;}
private:
  //TODO - base class should have input delegate pointer.  
  std::string text_; 
  ImageData character_;
  Font font_;
  int ticks_per_update_;
  int tick_;
};
