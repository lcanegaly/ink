#pragma once
#define GLEW_STATIC
#include "object.h"
#include "targa.h"
#include "glm.hpp"
#include "Renderer.h"
#include "input.h"

class ImageInterface  {
 public:
  virtual void Draw(int, int, int, int) = 0;
};

class DrawTexture : public RenderDelegate {
 public:
  DrawTexture(ObjectInterface* object, Renderer* renderer):context_{object}, renderer_{renderer}{
  }
//  ~DrawTexture(){
 //   delete image_;
 //   delete context_;
//    delete renderer_;
 // }
  virtual void Load(const char* filepath) override {
    image_ = new Targa::TgaImage(filepath);
    renderer()->LoadTexture((unsigned char*)image_->data(), 0, image_->width(), image_->height());
  }
  virtual void Draw() override {
    renderer()->Draw((unsigned char*)image_->data(), 0, context()->position().x , context()->position().y,
                     context()->size().x, context()->size().y);
  }
  virtual ObjectInterface* context() override {return context_;}
  virtual Renderer* renderer() override {return renderer_;}  
  virtual void Load() override {}
private:
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

class Button : public Object, public ImageInterface {
 public:
  Button(const char* filepath, Renderer* renderer); 
  Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y); 
  void Draw(int width, int height, int X, int Y) override; 
  void Update() override;
  void RegisterClickDelegate(Image* context, void(Image::*)());
 private:
  //TODO - should this be a dedicated delegate object.. like a trigger delegate?
  void (Image::* click_delegate_)();
  Image* trigger_;
  InputDelegate* inputDelegate_ptr_;
};

