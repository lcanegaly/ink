#pragma once
#include "object.h"
#include "targa/targa.h"
#include "renderer.h"
#include "vec2.h"
#include "glm.hpp"

class DrawSprite : public RenderDelegate {
 public:
  DrawSprite(ObjectInterface* object, ImageData& image_data);
  virtual void Draw();
  virtual ObjectInterface* context();
  virtual Renderer* renderer(); 
  virtual void Load();
  virtual void Load(const char* filepath); 
  
 private:
  ImageData& data_;
  Targa::Image* spriteSheet_;
  ObjectInterface* context_;
  Renderer* renderer_;
  int columns_;
  int rows_;
  int column_;
  int row_;
};

class Sprite : public Object {
 public:
  Sprite(const char* filepath, int width, int height, int X, int Y, int rows, int columns);
  virtual void SetIndex(int row, int column){
    data_.row = row;
    data_.column = column;
  }
 private:
  ImageData data_;
};
