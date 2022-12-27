#include "image.h"

Image::Image(const char* filepath, Renderer* renderer):
  Object(nullptr, new DrawTexture(this, renderer))
{
  Load(filepath);
}

Image::Image(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
 Object(nullptr, new DrawTexture(this, renderer))
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

