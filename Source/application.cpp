#include "application.h"
#include "image.h"
#include "fractal.h"
#include "button.h"
#include "sprite.h"
#include "textbox.h"
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
  TextBox* textbox = new TextBox("font1.tga", renderer_ptr_, 32, 32, 50, 100);
  Callback_T* callback = 
    new Callback<TextBox, std::string>(textbox, &TextBox::SetText, std::string("test test test"));
  Button* button = new Button("up.tga", renderer_ptr_, glm::vec2(50, 50), glm::vec2(50,200), callback);
  RegisterObject(button);
  RegisterObject(textbox);
}  


