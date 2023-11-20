#include <string>
#include <chrono>
#include <iostream>

#include "application.h"
#include "input.h"
#include "object.h"
#include "renderer.h"

Application::Application(const char* name, int width, int height)
  :window_{new GLFWContext(width, height, name)}, width_{width}, height_{height}
{
  running_ = true;
  GLFWInput input; 
  Renderer::Get().Init(width, height, window_.get());
  RegisterObjectList();
}

Application::~Application(){
  //for (auto& x : objects_){
  //  delete x;
  //}
}

void Application::Update(std::time_t delta_t ) {
  window_->PollEvents();
  for (auto& x : objects_){
    x->Update(delta_t);
  }
  OnUserUpdate();
}
void Application::Draw() {
  Renderer::Get().StartDraw();
  for (auto& x : objects_){
    x->Draw();
  }
  Renderer::Get().EndDraw();
}
void Application::RegisterObject(Object* object) {
  objects_.emplace_back(object);
}
void Application::RegisterObjectList() {
}  


