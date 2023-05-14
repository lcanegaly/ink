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
  unsigned char* buffer = (unsigned char*)image_->data(); 
  LineSegment(buffer, width, height, start_point.x, start_point.y, 
       end_point.x, end_point.y, brush_.stroke().thickness);
}

void LineVector(unsigned char* buffer, int width, int height, int x1, int y1, int vx, int vy, int magnitude){
  vx += x1;
  vy += y1;
  int dx = abs(vx - x1);
  int dy = abs(vy - y1);
  int sx = (x1 < vx) ? 1 : -1;
  int sy = (y1 < vy) ? 1 : -1;
  int err = dx - dy;
  int startx = x1;
  int starty = y1;

  while (x1 != width || y1 != height) {
    int err2 = 2 * err;
    if (err2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (err2 < dx) {
      err += dx;
      y1 += sy;
    }
    SetPixel(buffer, width, height, x1, y1, 0,255,0);
    int tx = x1 - startx;
    int ty = y1 - starty;
    if (sqrt(ty * ty + tx * tx) > magnitude) break;
  }
}

void LineSegment(unsigned char* buffer, int width, int height, int x1, int y1, int x2, int y2, int thickness){
  Vec2 normal = NormalOfLine(x1,y1,x2,y2); 
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;
  
  SetPixel(buffer, width, height, x1, y1, 0,255,0);
  while (x1 != x2 || y1 != y2) {
    int err2 = 2 * err;
    if (err2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (err2 < dx) {
      err += dx;
      y1 += sy;
    }
    LineVector(buffer,width,height, x1, y1, normal.x, normal.y, thickness);
    SetPixel(buffer, width, height, x1, y1, 0,255,0);
  }
}

void SetPixel(unsigned char* pixel_buffer, int buffer_width, int buffer_height, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= 0 && x < buffer_width && y >= 0 && y < buffer_height) {
        pixel_buffer[y * 3 * buffer_width + x * 3] = r;
        pixel_buffer[y * 3 * buffer_width + x * 3+1] = g;
        pixel_buffer[y * 3 * buffer_width + x * 3+2] = b;
    }
}

Vec2 NormalOfLine(int x1, int y1, int x2, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int ny = dx;
  int nx = -dy;
  return Vec2{ nx, ny };
}

bool isPointOnLine(int x, int y, int x1, int y1, int x2, int y2) {
    return (y - y1) * (x2 - x1) == (y2 - y1) * (x - x1);
}
