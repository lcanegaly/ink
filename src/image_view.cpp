#include <iostream>

#include "image_view.h"
#include "vec2.h"
#include "image.h"
#include "cmath"
#include "targa/targa.h"


ImageView::ImageView(Vec2 size, Vec2 position) 
  : Object(new NoUpdate(), new DrawTexture(this)), size_{size}, position_{position}, image_{nullptr}
{
  set_position(glm::vec2{position_.x, position_.y}, 0);
  set_size(glm::vec2{size_.x, size_.y});
  
  image_ = new Targa::TgaImage("");
  DrawTexture* renderer_ptr = (DrawTexture*)render_delegate();
  if (renderer_ptr){
    renderer_ptr->Load(image_);
  }
}

void ImageView::Draw(){
  render_delegate()->Draw();
} 

void ImageView::setBrush(Brush brush){
  brush_ = brush;
} 

void ImageView::Point(int diameter, Vec2 pos){
  const int color_depth = 3;
  const int width = image_->width();
  const int height = image_->height();
  unsigned char* buffer = (unsigned char*)image_->data(); 
  //test each pixel to see if it is in a radius.v
  std::cout << "width " << width << " height" << height << "\n"; 
  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      Vec2 distance = pos - Vec2{x,y};
      if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < diameter){ 
        buffer[ x * color_depth + ( y * width * color_depth) ] = brush_.color().red;
        buffer[ x * color_depth + ( y * width * color_depth) + 1 ] = brush_.color().green;
        buffer[ x * color_depth + ( y * width * color_depth) + 2 ] = brush_.color().blue;
      }
    }
  }
  
}
