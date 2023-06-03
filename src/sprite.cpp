#include "sprite.h"
#include <iostream>

DrawSprite::DrawSprite(ObjectInterface* object, ImageData& image_data):
  data_{image_data}, context_{object}
{}

void DrawSprite::Draw(){
  //TODO - LoadTexture should pull color depth
  Renderer::Get().LoadTexture((unsigned char*)spriteSheet_->data(), data_.bind_num, spriteSheet_->width(), spriteSheet_->height(), 3); 
  Renderer::Get().Draw(data_);
}
/*
ObjectInterface* DrawSprite::context(){
  return context_;
}
*/
void DrawSprite::Load(){}

void DrawSprite::Load(const char* filepath){
  spriteSheet_ = new Targa::TgaImage(filepath);
  data_.tex = (unsigned char*)spriteSheet_->data();
}

Sprite::Sprite(const char* filepath, int width, int height, int X, int Y, int rows, int columns):
    Object(new NoUpdate(), new DrawSprite(this, data_)) 
{
  data_.texture_rows = rows;
  data_.texture_columns = columns;
  set_size(glm::vec2(width, height));
  set_position(glm::vec2(X,Y), 0); //TODO, image constructor should take a rotation
  Load(filepath);
} 

