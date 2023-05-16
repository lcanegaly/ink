#pragma once
#include "object.h"
#include "image.h"
#include "callback.h"
#include "vec2.h"
#include <functional>

class Button : public Object {//, public ImageInterface {
 public:
  Button(const char* filepath); 
  Button(const char* filepath, int width, int height, int x, int y); 
  Button(const char* filepath, glm::vec2 size, glm::vec2 position, Callback_T* callback); 
  //void Draw(int width, int height, int x, int y) override; 
  void Update() override;
  void RegisterCallback(Callback_T* callback);
  void SetExecute(std::function<void()> func);
 private:
  InputDelegate* input_delegate_ptr_;
  Callback_T* callback_;
  bool clicked_; 
  std::function<void()> execute; 
};

