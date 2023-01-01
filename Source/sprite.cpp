#include "sprite.h"
#include <iostream>

DrawSprite::DrawSprite(ObjectInterface* object, ImageData& image_data, Renderer* renderer):
  context_{object}, data_{image_data}, renderer_{renderer} 
{}

void DrawSprite::Draw(){
  data_.bind_num = 1;
  data_.posX = context_->position().x;
  data_.posY = context_->position().y;
  data_.width = context_->size().x;
  data_.height = context_->size().y;
  data_.rotation = context_->rotation();
  renderer_->LoadTexture((unsigned char*)spriteSheet_->data(), data_.bind_num, spriteSheet_->width(), spriteSheet_->height()); 
  renderer_->Draw(data_);
}

ObjectInterface* DrawSprite::context(){
  return context_;
}
Renderer* DrawSprite::renderer(){
  return renderer_;
}

void DrawSprite::Load(){}

void DrawSprite::Load(const char* filepath){
  spriteSheet_ = new Targa::TgaImage(filepath);
  data_.tex = (unsigned char*)spriteSheet_->data();
}

Sprite::Sprite(const char* filepath, Renderer* renderer, int width, int height, int X, int Y, int rows, int columns):
    Object(new NoUpdate(), new DrawSprite(this, data_, renderer)) 
{
  data_.textureRows = rows;
  data_.textureColumns = columns;
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO, image constructor should take a rotation
  Load(filepath);
} 

