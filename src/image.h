#pragma once
#include <iostream>

#include "object.h"
#include "targa/targa.h"
#include "glm.hpp"
#include "renderer.h"
#include "input.h"


class DrawTexture : public RenderDelegate {
 public:
  DrawTexture(ObjectInterface* object);
  virtual void Load(const char* filepath) override;
  virtual void Load(PixelBuffer buffer) override;
  virtual void Draw() override;
  virtual void Load() override {}
  ~DrawTexture(){ delete buffer_.data; }
 
 private:
  static int texture_counter_;
  int texture_slot_;
  ObjectInterface* context_;
  Renderer* renderer_;
  PixelBuffer buffer_;
};

class Image : public Object {
 public:
  Image();  
  Image(const char* filepath); 
  Image(const char* filepath, int width, int height, int X, int Y); 
};


