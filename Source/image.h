#pragma once
#define GLEW_STATIC
#include "object.h"
#include "targa.h"
#include "glm.hpp"
#include "Renderer.h"

class ImageInterface  {
 public:
  virtual void Draw(int, int, int, int) = 0;
};

class DrawTexture : public RenderDelegate {
 public:
  DrawTexture(ObjectInterface* object, Renderer* renderer):RenderDelegate(object, renderer){
  }
  virtual void Load(const char* filepath) override {
    image_ = new Targa::TgaImage(filepath);
    renderer()->LoadTexture((unsigned char*)image_->data(), 0, image_->width(), image_->height());
  }
  virtual void Draw() override {
    renderer()->Draw((unsigned char*)image_->data(), 0, context()->position().x , context()->position().y,
                     context()->size().x, context()->size().y);
  }
private:
  Targa::Image* image_;
};

class Image : public Object, public ImageInterface {
 public:
  Image(const char* filepath, Renderer* renderer); 
  Image(const char* filepath, Renderer* renderer, int width, int height, int X, int Y); 
  void Draw(int width, int height, int X, int Y);
};

