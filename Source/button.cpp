#include "button.h"

//TODO.. Updatedelegate should actually do something. 
Button::Button(const char* filepath, Renderer* renderer):
  Object(new ButtonUpdate, new DrawTexture(this, renderer)), 
  trigger_{nullptr}, trigger_fractal_{nullptr}, 
  click_delegate_fractal_{nullptr}, click_delegate_{nullptr}
{
  Load(filepath);
}

Button::Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
 Object(new ButtonUpdate, new DrawTexture(this, renderer)), inputDelegate_ptr_{new EmscriptenInput()}
{
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  Load(filepath);
}

void Button::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  render_delegate()->Draw();
}

void Button::Update() {
  if (inputDelegate_ptr_->GetMouseClick()) {
		int x = std::abs(inputDelegate_ptr_->GetMousePosition().x - this->position().x);
		int y = std::abs(inputDelegate_ptr_->GetMousePosition().y - this->position().y);

		if ( (x <= 0.5 * this->size().x) && ( y <= 0.5 * this->size().y ))
		{
      inputDelegate_ptr_->Reset();
			LOG("Button Clicked");
      if (trigger_) ((*trigger_).*click_delegate_)();

      if (trigger_fractal_) ((*trigger_fractal_).*click_delegate_fractal_)();
    }
	}
}
//TODO templated to find object type..
void Button::RegisterClickDelegate(Image* context, void(Image::* click_delegate)()) {
  click_delegate_ = click_delegate;
  trigger_ = context;
}

void Button::RegisterClickDelegate(Fractal* context, void(Fractal::* click_delegate)()) {
  click_delegate_fractal_ = click_delegate;
  trigger_fractal_ = context;
}



