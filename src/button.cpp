#include <chrono>

#include "button.h"
#include "audio.h"
#include "log.h"

//TODO.. Updatedelegate should actually do something. 
Button::Button(const char* filepath):
  Object(new ButtonUpdate, new DrawTexture(this)), 
  input_delegate_ptr_{new GLFWInput()}, callback_{nullptr}, clicked_{false}
{
  Load(filepath);
}

Button::Button(const char* filepath, int width, int height, int X, int Y): 
  Object(new ButtonUpdate, new DrawTexture(this), new SoundEffect("click.wav")), input_delegate_ptr_{new GLFWInput()}, 
  callback_{nullptr}, clicked_{false}
{
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

Button::Button(const char* filepath, glm::vec2 size, glm::vec2 position, Callback_T* callback) : 
  Object(new ButtonUpdate, new DrawTexture(this)), input_delegate_ptr_{new EmscriptenInput()}, 
  callback_{callback}, clicked_{false}
{
  set_size(size);
  set_position(position, 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

void Button::Update(std::time_t delta_t) {
  elapsed_time_ += delta_t; 
  if (elapsed_time_ > 1500){
    if (input_delegate_ptr_){
      if (input_delegate_ptr_->GetKey(65)) {
        LOG("BUTTON PRESSED\n");
        LOG("resetting timer\n");
        elapsed_time_ = 0;
        if(audio()){
          audio()->PlaySound();
        }
      }
    }
  }

  if (input_delegate_ptr_->GetMouseClick()) {
		int x = std::abs(input_delegate_ptr_->GetMousePosition().x - this->position().x);
		int y = std::abs(input_delegate_ptr_->GetMousePosition().y - this->position().y);

		if ( (x <= 0.5 * this->size().x) && ( y <= 0.5 * this->size().y ))
		{
      if(audio()){
        LOG("Button clicked\n");
        audio()->PlaySound();
      }
      
      if (execute != nullptr){
        execute();
      } 
      input_delegate_ptr_->Reset();
      if (callback_) {
        callback_->Call();
      } 
    }
	}
}


void Button::SetExecute(std::function<void()> f){
  execute = f;
}
