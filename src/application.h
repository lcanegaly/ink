#pragma once
#include <chrono>
#include <memory>
#include <vector>

#include "window.h"

class Object;
class Renderer;

class Application {
 public:
  Application(const char* name, int width, int height);
  ~Application();
  void Update(std::time_t delta_t );
  void Draw();
  void RegisterObject(Object* object);
  void RegisterObjectList(); 
  virtual void OnUserUpdate(){}
  bool shouldClose(){return window_->shouldClose();}
  void Close(){window_->Destroy();}
 private:
  std::unique_ptr<WindowDelegate> window_;
  std::vector<std::unique_ptr<Object>> objects_;
  int width_;
  int height_;
};

//to be defined by client app
extern std::unique_ptr<Application> CreateApplication();
