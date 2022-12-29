#pragma once
#include "object.h"
#include "image.h"
#include "fractal.h"

class Button : public Object, public ImageInterface {
 public:
  Button(const char* filepath, Renderer* renderer); 
  Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y); 
  void Draw(int width, int height, int X, int Y) override; 
  void Update() override;

  void RegisterClickDelegate(Image* context, void(Image::*)());
  void RegisterClickDelegate(Fractal* context, void(Fractal::*)());
 private:
  //TODO - should this be a dedicated delegate object.. like a trigger delegate?
  void (Image::* click_delegate_)();
  //TODO - fix this hack
  void (Fractal::* click_delegate_fractal_)();
  Image* trigger_;
  Fractal* trigger_fractal_;
  InputDelegate* inputDelegate_ptr_;
};

