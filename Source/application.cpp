#include "application.h"
#include "image.h"

Application::Application(const char* name, int width, int height, Renderer* renderer)
  :renderer_ptr_{renderer}
{
  renderer_ptr_->Init(width, height, new GLFWContext(width, height, name));
  RegisterObjectList();
}

Application::~Application(){
  for (auto& x : objects_){
    delete x;
  }
}

void Application::Update() {
  for (auto x : objects_){
    x->Update();
  }
}
void Application::Draw() {
  for (Object* x : objects_){
    x->Draw();
  }
}
void Application::RegisterObject(Object* object) {
  objects_.push_back(object);
}
void Application::RegisterObjectList() {
  RegisterObject(new Image("up.tga", renderer_ptr_, 50, 50, 100, 100));
}  


