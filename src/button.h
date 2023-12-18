#pragma once
#include <functional>
#include <chrono>

#include "object.h"
#include "callback.h"
#include "vec2.h"
#include "input.h"

class Clickable : public UpdateDelegate {
 public:
  Clickable();
  Clickable(Object* context);
  virtual void Update(std::time_t delta_t);
  void SetExecute(std::function<void()> func);
  bool clicked_ = false; 

 private:
  bool IsClicked();
  Object* context_;
  std::unique_ptr<InputDelegate> input_delegate_;
  std::function<void()> execute_; 
};

class Button : public Object {
 public:
  Button(const char* filepath); 
  Button(const char* filepath, int width, int height, int x, int y); 
  void Update(std::time_t delta_t) override  
  {update_delegate().Update(delta_t);}
  void SetExecute(std::function<void()> func);
  bool active(); 
};

