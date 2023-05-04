#include <cmath>

#include "image.h"

int DrawTexture::texture_counter_ = 0; 

Image::Image(const char* filepath):
  Object(new ButtonUpdate, new DrawTexture(this))
{
  Load(filepath);
}

//TODO , make default update delegate
Image::Image(const char* filepath, int width, int height, int X, int Y): 
 Object(new ButtonUpdate, new DrawTexture(this))
{
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO, image constructor should take a rotation
  Load(filepath);
}

void Image::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0);
  render_delegate()->Draw();
}


