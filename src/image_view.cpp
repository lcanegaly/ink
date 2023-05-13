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
  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      Vec2 distance = pos - Vec2{x,y};
      if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < diameter){ 
        SetPixel(buffer, width, height, x, y, 0, 255, 0); 
      }
    }
  }
  
}

void ImageView::DrawLine(Vec2 start_point,Vec2 end_point) {
  const int width = image_->width();
  const int height = image_->height();

  //test each pixel to see if it is on the line
  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      if (isPointOnLine(x,y,start_point.x, start_point.y, end_point.x, end_point.y)){ 
        Point(brush_.stroke().thickness, Vec2{x,y}); 
      }
    }
  }
  
}

void SetPixel(unsigned char* pixel_buffer, int buffer_width, int buffer_height, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 0 && x < buffer_width && y >= 0 && y < buffer_height) {
        pixel_buffer[y * 3 * buffer_width + x * 3] = r;
        pixel_buffer[y * 3 * buffer_width + x * 3+1] = g;
        pixel_buffer[y * 3 * buffer_width + x * 3+2] = b;
    }
}

bool isPointOnLine(int x, int y, int x1, int y1, int x2, int y2) {
    // Check if the point is on the line defined by (x1, y1) and (x2, y2)
    return (y - y1) * (x2 - x1) == (y2 - y1) * (x - x1);
}
