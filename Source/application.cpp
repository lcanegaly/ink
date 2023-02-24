#include "application.h"
#include "image.h"
#include "fractal.h"
#include "button.h"
#include "sprite.h"
#include "textbox.h"
#include "label.h"
#include "input.h"
#include "glm.hpp"
#include <string>
#include <iostream>

Application::Application(const char* name, int width, int height)
  :width_{width}, height_{height}
{
  renderer_ptr_ = &Renderer::Get();
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
  OnUserUpdate();
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
  
}  
Renderer* Application::renderer_ptr(){
  return renderer_ptr_;
}


