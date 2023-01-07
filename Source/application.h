#pragma once
#include <vector>
#include "object.h"

class Application {
 public:
  Application(const char* name, int width, int height, Renderer* renderer);
  ~Application();
  void Update();
  void Draw();
  void RegisterObject(Object* object);
  virtual void RegisterObjectList(); //Objects created here for now. 
  Renderer* renderer_ptr();
  virtual void OnUserUpdate(){}
 private:
  Renderer* renderer_ptr_;
  std::vector<Object*> objects_;
  int width_;
  int height_;
};


