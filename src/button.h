#pragma once
#include <functional>
#include <chrono>

#include "object.h"
#include "image.h"
#include "callback.h"
#include "vec2.h"

class Button : public Object {
 public:
  Button(const char* filepath); 
  Button(const char* filepath, int width, int height, int x, int y); 
  Button(const char* filepath, glm::vec2 size, glm::vec2 position, 
      Callback_T* callback); 
  void Update(std::time_t delta_t) override;
  void RegisterCallback(Callback_T* callback);
  void SetExecute(std::function<void()> func);
  bool active(); 
 
 private:
  bool IsClicked();

 private:
  std::unique_ptr<InputDelegate> input_delegate_;
  Callback_T* callback_;
  bool clicked_ = false; 
  std::function<void()> execute; 
};

