#pragma once
#include <iostream>
#include "object.h"
#include "targa/targa.h"
#include "glm.hpp"
#include "renderer.h"
#include "input.h"


//TODO - Delete this function
class ImageInterface  {
 public:
  virtual void Draw(int, int, int, int) = 0;
};

class DrawTexture : public RenderDelegate {
 public:
  DrawTexture(ObjectInterface* object):image_{nullptr}, context_{object}, renderer_{&Renderer::Get()} {
    texture_slot_ = 1; 
  }
  virtual void Load(const char* filepath) override {
    if (buffer_.data != nullptr){
     delete buffer_.data; 
    } 
    buffer_ = Targa::TgaImage::Load(filepath);
    //image_ = new Targa::TgaImage(filepath);
     
  }
  virtual void Load(PixelBuffer buffer) {
    buffer_ = buffer;
  }
  virtual void Draw() override {
    renderer()->LoadTexture((unsigned char*)image_->data(), texture_slot_, image_->width(), image_->height(), image_->pixel_depth()/8);
    renderer()->Draw((unsigned char*)image_->data(), texture_slot_, context_->position().x , context_->position().y,
                     context_->size().x, context_->size().y, context_->rotation());
  }
  virtual ObjectInterface* context() override {return context_;}
  virtual Renderer* renderer() override {return renderer_;}  
  virtual void Load() override {}
  
  ~DrawTexture(){ delete image_; }
private:
  static int texture_counter_;
  int texture_slot_;
  //Targa::Image* image_;
  ObjectInterface* context_;
  Renderer* renderer_;
  PixelBuffer buffer_;
};

class Image : public Object, public ImageInterface {
 public:
  Image();  
  Image(const char* filepath); 
  Image(const char* filepath, int width, int height, int X, int Y); 
  void Draw(int width, int height, int X, int Y) override;
};


