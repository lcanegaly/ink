#pragma once
#define GLEW_STATIC
#include "object.h"
#include "targa.h"
#include "glm.hpp"
#include "renderer.h"
#include "input.h"

class ImageInterface  {
 public:
  virtual void Draw(int, int, int, int) = 0;
};

class DrawTexture : public RenderDelegate {
 public:
  DrawTexture(ObjectInterface* object, Renderer* renderer):context_{object}, renderer_{renderer}{
    //textureSlot_ = textureCounter_++;
    textureSlot_ = 1; //textureCounter_++;
  }
  virtual void Load(const char* filepath) override {
    image_ = new Targa::TgaImage(filepath);
    //renderer()->LoadTexture((unsigned char*)image_->data(), textureSlot_, image_->width(), image_->height());
  }
  virtual void Draw() override { 
    renderer()->LoadTexture((unsigned char*)image_->data(), textureSlot_, image_->width(), image_->height());
    renderer()->Draw((unsigned char*)image_->data(), textureSlot_, context_->position().x , context_->position().y,
                     context_->size().x, context_->size().y, context_->rotation());
  }
  virtual ObjectInterface* context() override {return context_;}
  virtual Renderer* renderer() override {return renderer_;}  
  virtual void Load() override {}
private:
  static int textureCounter_;
  int textureSlot_;
  Targa::Image* image_;
  ObjectInterface* context_;
  Renderer* renderer_;
};

class Image : public Object, public ImageInterface {
 public:
  Image(const char* filepath, Renderer* renderer); 
  Image(const char* filepath, Renderer* renderer, int width, int height, int X, int Y); 
  void Draw(int width, int height, int X, int Y) override;
  void Test() {printf("TEST TEST TEST\n");}
};


