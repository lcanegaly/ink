#pragma once
#include "object.h"
#include "image.h"
#include "fractal.h"
#include "callback.h"
#include "vec2.h"
#include <functional>

class Button : public Object, public ImageInterface {
 public:
  Button(const char* filepath, Renderer* renderer); 
  Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y); 
  Button(const char* filepath, Renderer* renderer, glm::vec2 size, glm::vec2 position, Callback_T* callback); 
  void Draw(int width, int height, int X, int Y) override; 
  void Update() override;
  void RegisterCallback(Callback_T* callback);
  void SetExecute(std::function<void()> f);
 private:
  InputDelegate* inputDelegate_ptr_;
  Callback_T* callback_;
  bool clicked_; 
  std::function<void()> execute; 
};

