#include "application.h"
#include "image.h"
#include "log.h"
#include <string>

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
  for (Object* x : objects_){
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
  //RegisterObject(new Image("up.tga", renderer_ptr_, 50, 50, 200, 200));
  Image* i = new Image("up.tga", renderer_ptr_, 50, 50, 100, 100);
  i->set_name(std::string("image"));
  Button* b = new Button("down.tga", renderer_ptr_, 50, 50, 250, 100);
  b->set_name(std::string("button"));
  //Object* o = new Object(nullptr, nullptr); 
  //o->set_name(std::string("object"));


  b->RegisterClickDelegate(i, &Image::Test);
  
  RegisterObject(i);
  RegisterObject(b); 
  //RegisterObject(o);
  
}  


