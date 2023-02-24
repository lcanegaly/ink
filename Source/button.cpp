#include "button.h"

//TODO.. Updatedelegate should actually do something. 
Button::Button(const char* filepath, Renderer* renderer):
  Object(new ButtonUpdate, new DrawTexture(this, renderer)), 
  inputDelegate_ptr_{new EmscriptenInput()}, callback_{nullptr}, clicked_{false}

{
  Load(filepath);
}

Button::Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
  Object(new ButtonUpdate, new DrawTexture(this, renderer)), inputDelegate_ptr_{new EmscriptenInput()}, 
  callback_{nullptr}, clicked_{false}

{
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

Button::Button(const char* filepath, Renderer* renderer, glm::vec2 size, glm::vec2 position, Callback_T* callback) : 
  Object(new ButtonUpdate, new DrawTexture(this, renderer)), inputDelegate_ptr_{new EmscriptenInput()}, 
  callback_{callback}, clicked_{false}
{
  
  set_size(size);
  set_position(position, 0); //TODO - fix, should take rotation from constructor.
  Load(filepath);
}

void Button::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO fix, draw should take a rotation. 
  render_delegate()->Draw();
}

void Button::Update() {
  if (inputDelegate_ptr_->GetMouseClick()) {
		int x = std::abs(inputDelegate_ptr_->GetMousePosition().x - this->position().x);
		int y = std::abs(inputDelegate_ptr_->GetMousePosition().y - this->position().y);

		if ( (x <= 0.5 * this->size().x) && ( y <= 0.5 * this->size().y ))
		{
      inputDelegate_ptr_->Reset();
      if (callback_) {
        callback_->Call();
      } 
    }
	}
}


