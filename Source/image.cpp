#include "image.h"
#include <cmath>


int DrawTexture::textureCounter_ = 0; 

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
  set_position(glm::vec2(X,Y), 0); //TODO, image constructor should take a rotation
  Load(filepath);
}

void Image::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0);
  render_delegate()->Draw();
}


