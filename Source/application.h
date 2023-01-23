#pragma once
#include <vector>

class Object;
class Renderer;

class Application {
 public:
  Application(const char* name, int width, int height);
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

//to be defined by client app
extern Application* CreateApplication();
