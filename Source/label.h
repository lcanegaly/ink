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
  Label(const char* filepath, Renderer* renderer, int width, int height, int X, int Y);
  Label(const char* filepath, Renderer* renderer, int width, int height, int X, int Y, 
        std::function<void()> scriptFunc);
  void SetupFont();
  void Update()override; 
  void SetText(const std::string text);
private:
  //TODO - base class should have input delegate pointer. 
  std::string text_; 
  ImageData character_;
  Font font_;
};
