#include "image.h"

Image::Image(const char* filepath, Renderer* renderer):
  Object(new UpdateDelegate(this), new DrawTexture(this, renderer))
{
  printf("inside Image constructor. this object is %p \n", (void*)this);
  printf("inside Image constructor. renderer delegate ptr returns %p \n", (void*)render_delegate());
  printf("inside Image constructor. renderer delegate context (image..) returns %p \n", (void*)render_delegate()->context());
  //set_size(glm::vec2(20, 20));
  //set_position(glm::vec2(20,20));
  
  printf("inside Image constructor. this object size is..  %f, %f \n", size().x, size().y); 
  Load(filepath);
}

Image::Image(const char* filepath, Renderer* renderer, int width, int height, int X, int Y): 
 Object(new UpdateDelegate(this), new DrawTexture(this, renderer))
{
  printf("inside Image constructor with width/xy. this object is %p \n", (void*)this);
  printf("inside Image constructor. renderer delegate ptr returns %p \n", (void*)render_delegate());
  printf("inside Image constructor. renderer delegate context (image..) returns %p \n", (void*)render_delegate()->context());
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  
  printf("inside Image constructor. this object size is..  %f, %f \n", size().x, size().y); 
  Load(filepath);
}


void Image::Draw(int width, int height, int X, int Y) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y));
  render_delegate()->Draw();
}

