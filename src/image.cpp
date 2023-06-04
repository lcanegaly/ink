#include <cmath>

#include "image.h"

int DrawTexture::texture_counter_ = 0; 
DrawTexture::DrawTexture(ObjectInterface* object):context_{object}, 
      renderer_{&Renderer::Get()} {
  texture_slot_ = 1; 
}

void DrawTexture::Load(const char* filepath) {
  if (buffer_.data != nullptr){
    delete buffer_.data; 
  } 
  buffer_ = Targa::LoadTga(filepath);
}

void DrawTexture::Load(PixelBuffer buffer) {
    buffer_ = buffer;
}

void DrawTexture::Draw() {
  Renderer::Get().LoadTexture((unsigned char*)buffer_.data, texture_slot_, 
      buffer_.width, buffer_.height, buffer_.color_channels);
  Renderer::Get().Draw((unsigned char*)buffer_.data, texture_slot_, 
      context_->position().x , context_->position().y, context_->size().x, 
      context_->size().y, context_->rotation());
}

Image::Image():
  Object(new NoUpdate, new DrawTexture(this)) {
  Load(""); 
}

Image::Image(const char* filepath):
  Object(new NoUpdate, new DrawTexture(this)) {
  Load(filepath);
}

Image::Image(const char* filepath, int width, int height, int X, int Y): 
 Object(new NoUpdate, new DrawTexture(this)) {
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO, image constructor should take a rotation
  Load(filepath);
}


