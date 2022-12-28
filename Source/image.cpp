#include "image.h"
#include <cmath>

Image::Image(const char* filepath, Renderer* renderer):
  Object(new ButtonUpdate, new DrawTexture(this, renderer))
{
  Load(filepath);
}

//TODO , make default update delegate
Image::Image(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
 Object(new ButtonUpdate, new DrawTexture(this, renderer))
{
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  Load(filepath);
}

void Image::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  render_delegate()->Draw();
}


//TODO.. Updatedelegate should actually do something. 
Button::Button(const char* filepath, Renderer* renderer):
  Object(new ButtonUpdate, new DrawTexture(this, renderer))
{
  Load(filepath);
}

Button::Button(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
 Object(new ButtonUpdate, new DrawTexture(this, renderer)), inputDelegate_ptr_{new EmscriptenInput()}
{
  LOG("in button constructor");
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
  //printf("Button contains : %f, %f, %d \n", inputDelegate_ptr_->GetMousePosition().x, inputDelegate_ptr_->GetMousePosition().y, inputDelegate_ptr_->GetMouseClick());
  if (inputDelegate_ptr_->GetMouseClick()) {
		int x = std::abs(inputDelegate_ptr_->GetMousePosition().x - this->position().x);
		int y = std::abs(inputDelegate_ptr_->GetMousePosition().y - this->position().y);

		if ( (x <= 0.5 * this->size().x) && ( y <= 0.5 * this->size().y ))
		{
      inputDelegate_ptr_->Reset();
			LOG("Button Clicked");
		  ((*trigger_).*click_delegate_)();
    }
	}
}
//TODO templated to find object type..
void Button::RegisterClickDelegate(Image* context, void(Image::* click_delegate)()) {
  click_delegate_ = click_delegate;
  trigger_ = context;
}


