#include "application.h"
#include "image.h"
#include "fractal.h"
#include "button.h"
#include "glm.hpp"
#include <string>

Application::Application(const char* name, int width, int height, Renderer* renderer)
  :renderer_ptr_{renderer}, width_{width}, height_{height}
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
  Fractal* f = new Fractal(glm::vec2(width_, height_), glm::vec2(0.0, 0.0), renderer_ptr_); 
  RegisterObject(f);

  Button* up = new Button("up.tga", renderer_ptr_, 50, 50, 250, 100);
  up->RegisterClickDelegate(f, &Fractal::Up);
  Button* down = new Button("down.tga", renderer_ptr_, 50, 50, 250, 200);
  down->RegisterClickDelegate(f, &Fractal::Down);
  Button* left = new Button("left.tga", renderer_ptr_, 50, 50, 200, 150);
  left->RegisterClickDelegate(f, &Fractal::Left);
  Button* right = new Button("right.tga", renderer_ptr_, 50, 50, 300, 150);
  right->RegisterClickDelegate(f, &Fractal::Right);
  Button* in = new Button("plus.tga", renderer_ptr_, 50, 50, 100, 200);
  in->RegisterClickDelegate(f, &Fractal::In);
  Button* out = new Button("minus.tga", renderer_ptr_, 50, 50, 100, 250);
  out->RegisterClickDelegate(f, &Fractal::Out);

  RegisterObject(up); 
  RegisterObject(down); 
  RegisterObject(left); 
  RegisterObject(right); 
  RegisterObject(in); 
  RegisterObject(out); 
}  


