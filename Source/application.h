#pragma once
#include <vector>
//#include "Renderer.h"
#include "object.h"


class Application {
 public:
  Application(const char* name, int width, int height, Renderer* renderer);
  ~Application();
  void Update();
  void Draw();
  void RegisterObject(Object* object);
  void RegisterObjectList(); //Objects created here for now. 
 private:
  Renderer* renderer_ptr_;
  std::vector<Object*> objects_;
};
