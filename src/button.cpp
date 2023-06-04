#include <chrono>

#include "button.h"
#include "audio.h"
#include "log.h"

//TODO.. Updatedelegate should actually do something. 
Button::Button(const char* filepath):
    Object(new ButtonUpdate, new DrawTexture(this)), 
    input_delegate_{new GLFWInput()}, callback_{nullptr} {
  Load(filepath);
}

Button::Button(const char* filepath, int width, int height, int X, int Y): 
    Object(new ButtonUpdate, new DrawTexture(this), new Silent()), 
    input_delegate_{new GLFWInput()}, callback_{nullptr} {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

Button::Button(const char* filepath, glm::vec2 size, glm::vec2 position,
    Callback_T* callback): Object(new ButtonUpdate, new DrawTexture(this)), 
    input_delegate_{new EmscriptenInput()}, callback_{callback} {
  set_size(size);
  set_position(position, 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

bool Button::active() {
  if (clicked_) {
    clicked_ = false;
    return true;
  }
  return false;
}

bool Button::IsClicked() {
  if (input_delegate_->GetMouseClick()) {
    int x = std::abs(input_delegate_->GetMousePosition().x - position().x);
		int y = std::abs(input_delegate_->GetMousePosition().y - position().y);
    elapsed_time_ = 0;
		if ( (x <= 0.5 * size().x) && ( y <= 0.5 * size().y )) {
      clicked_ = true;
      return true; 
    }
  }
  return false;
}

void Button::Update(std::time_t delta_t) {
  elapsed_time_ += delta_t; 
  if (elapsed_time_ > 300){
    if (IsClicked()){
      if (execute != nullptr){
        execute();
      } 
      if (callback_) {
        callback_->Call();
      } 
    }
  }
}

void Button::SetExecute(std::function<void()> f){
  execute = f;
}
