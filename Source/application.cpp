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
  :window_{new GLFWContext(width, height, name)}, width_{width}, height_{height}
{
  renderer_ptr_ = &Renderer::Get();
  EmscriptenInput input; 
  renderer_ptr_->Init(width, height, window_);
  RegisterObjectList();
}

Application::~Application(){
  for (auto& x : objects_){
    delete x;
  }
}

void Application::Update() {
  window_->PollEvents();
  for (Object* x : objects_){
    x->Update();
  }
  OnUserUpdate();
}
void Application::Draw() {
  Renderer::Get().StartDraw();
  for (Object* x : objects_){
    x->Draw();
  }
  Renderer::Get().EndDraw();
}
void Application::RegisterObject(Object* object) {
  objects_.push_back(object);
}
void Application::RegisterObjectList() {
}  
Renderer* Application::renderer_ptr(){
  return renderer_ptr_;
}


