#pragma once
#include <chrono>
#include <memory>
#include <vector>

#include "window.h"
#include "object.h"
//class Object;
class Renderer;

class Application {
 public:
  Application(const char* name, int width, int height);
  ~Application();
  void Update(std::time_t delta_t );
  void Draw();
  void RegisterObject(Object* object);
  void RegisterObjectList(); 
  virtual void OnUserUpdate(std::time_t delta_t){}
  bool shouldClose(){return window_->shouldClose() | !running_;}
  void Close(){
    running_ = false;
    window_->Destroy();}
  std::vector<std::unique_ptr<Object>> objects_;
 private:
  std::unique_ptr<WindowDelegate> window_;
  int width_;
  int height_;
  bool running_;
};

//to be defined by client app
extern std::unique_ptr<Application> CreateApplication();
