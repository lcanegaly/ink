#pragma once
#include <vector>
#include "window.h"

class Object;
class Renderer;

class Application {
 public:
  Application(const char* name, int width, int height);
  ~Application();
  void Update();
  void Draw();
  void RegisterObject(Object* object);
  void RegisterObjectList(); 
  Renderer* renderer_ptr();
  virtual void OnUserUpdate(){}
  bool shouldClose(){return window_->shouldClose();}
  void Close(){window_->Destroy();}
 private:
  WindowDelegate* window_;
  Renderer* renderer_ptr_;
  std::vector<Object*> objects_;
  int width_;
  int height_;
};

//to be defined by client app
extern Application* CreateApplication();
