#pragma once
#include <vector>
//#include "Renderer.h"
#include "object.h"

class Application {
 public:
  Application(const char* name, int width, int height){}
  void Update(){}
  void Draw(){}
  void RegisterObject(Object* object){}
 private:
  //Renderer* renderer_ptr_;
  std::vector<Object *> objects_;
};
