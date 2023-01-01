#include "application.h"
#include "image.h"
#include "fractal.h"
#include "button.h"
#include "sprite.h"
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
  //Button* out = new Button("corn.tga", renderer_ptr_, 128, 128, 200, 250);
  Sprite* s = new Sprite("font1.tga", renderer_ptr_, 128, 128, 150, 150, 8, 16 );
  //out->RegisterClickDelegate(f, &Fractal::Out);
  s->SetIndex(7,0);
  RegisterObject(s); 
}  


