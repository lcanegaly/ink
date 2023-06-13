#include <chrono>

#include "button.h"
#include "audio.h"
#include "log.h"

Clickable::Clickable() : input_delegate_{new GLFWInput()}{}

Clickable::Clickable(Object* context):context_{context}, 
  input_delegate_{new GLFWInput()} {}

bool Clickable::IsClicked() {
  if (input_delegate_->GetMouseClick()) {
    int x = std::abs(input_delegate_->GetMousePosition().x 
        - context_->position().x);
		int y = std::abs(input_delegate_->GetMousePosition().y 
        - context_->position().y);
    context_->elapsed_time_ = 0;
		if ( (x <= 0.5 * context_->size().x) && ( y <= 0.5 * context_->size().y )) {
      clicked_ = true;
      return true; 
    }
  }
  return false;
}

void Clickable::Update(std::time_t delta_t) {
  context_->elapsed_time_ += delta_t; 
  if (context_->elapsed_time_ > 300){
    if (IsClicked()){
      if (execute_ != nullptr){
        execute_();
      } 
    }
  }
}

void Clickable::SetExecute(std::function<void()> f){
 execute_ = f;
}

Button::Button(const char* filepath):
    Object(new Clickable(this), new DrawTexture(this)) {
  Load(filepath);
}

Button::Button(const char* filepath, int width, int height, int X, int Y): 
    Object(new Clickable(this), new DrawTexture(this), new Silent()) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

bool Button::active() {
  if (((Clickable&)update_delegate()).clicked_) {
    ((Clickable&)update_delegate()).clicked_ = false;
    return true;
  }
  return false;
}

void Button::SetExecute(std::function<void()> f){
 ((Clickable&)update_delegate()).SetExecute(f);
}
