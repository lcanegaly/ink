#include "application.h"
#include "image.h"
#include "fractal.h"
#include "button.h"
#include "input.h"
#include "glm.hpp"
#include <string>

Application::Application(const char* name, int width, int height, Renderer* renderer)
  :renderer_ptr_{renderer}, width_{width}, height_{height}
{
  //TODO - emscripteninput should not set callbacks in constructor. 
  EmscriptenInput input; 
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
    if (x->rotation() > 360.0){
      x->set_position(x->position(), 0.0);
    }else{
      x->set_position(x->position(), x->rotation()+1);
    }
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

  for (int i = 0; i < 1; i++)
    RegisterObject(new Image("corn.tga", renderer_ptr_, width_/2, 3, width_/2, 50*i+50));


  //Button* out = new Button("minus.tga", renderer_ptr_, 50, 50, 100, 250);
  //out->RegisterClickDelegate(f, &Fractal::Out);

  //RegisterObject(out); 
}  


