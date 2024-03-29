#include <functional>

#include "image_view.h"
#include "vec2.h"
#include "cmath"
#include "targa/targa.h"

ImageView::ImageView(IVec2 size, IVec2 position) : Object(new NoUpdate(), 
    new Invisible()) {
  set_position(glm::vec2{position_.x, position_.y}, 0);
  set_size(glm::vec2{size_.x, size_.y});
  const int color_channels = 4;
  buffer_ = PixelBuffer{
    new unsigned char [static_cast<int>(size_.x) * static_cast<int>(size_.y) * color_channels],
    size_.x,
    size_.y,
    color_channels 
  };
  //render_delegate().Load(buffer_);
}

// TODO needs refactored
void ImageView::Draw(){ render_delegate().Draw(); } 

void ImageView::setBrush(Brush brush){ brush_ = brush; } 

void ImageView::Clear(Color color) { 
  PixelBuffer& buff = buffer_;
  ForEachPixel([](int, int){return true;}, [buff, color](int x, int y){
      SetPixel((unsigned char*)buff.data, buff.width, buff.height, IVec2{x, y}, 
          color); } 
      );
}

void ImageView::ForEachPixel(std::function<bool(int x, int y)> test_condition,
    std::function<void(int x,int y)> action) {
  const int width = buffer_.width;
  const int height = buffer_.height;
  for (int x = 0; x < width; x++){
    for (int y = 0; y < height; y++){
      if (test_condition(x,y))
        action(x,y);
    }
  }
} 

void ImageView::Point(int diameter, IVec2 pos) {
  PixelBuffer& buff = buffer_;
  std::function<bool(int,int)> test = [diameter, pos, buff](int x, int y) {
      if (IsInRadius(diameter / 2, pos, x, y))
        return true;
      return false; 
  };
  Color color = brush_.color(); 
  std::function<void(int,int)> action = [buff, color](int x, int y) {
      SetPixel((unsigned char*)buff.data , buff.width, buff.height, IVec2{x, y}, 
          color); 
  };
  ForEachPixel(test, action);
}

void ImageView::Line(IVec2 start_point,IVec2 end_point) {
  const int width = buffer_.width;
  const int height = buffer_.height;
  unsigned char* buffer = (unsigned char*)buffer_.data; 
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
    SetPixel(buffer, width, height, IVec2{x1, y1}, Color{0, 255, 0, 255});
    int tx = x1 - startx;
    int ty = y1 - starty;
    if (sqrt(ty * ty + tx * tx) > magnitude) break;
  }
}

void LineSegment(unsigned char* buffer, int width, int height, int x1, int y1, int x2, int y2, int thickness){
  IVec2 normal = NormalOfLine(x1,y1,x2,y2); 
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;
  
  SetPixel(buffer, width, height, IVec2{x1, y1}, Color{0, 255, 0, 255});
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
    SetPixel(buffer, width, height, IVec2{x1, y1}, Color{0, 255, 0, 255});
  }
}

void SetPixel(unsigned char* pixel_buffer, int buffer_width, int buffer_height, 
              IVec2 position, Color color) {
  const int color_channels = 4; 
  int x = position.x;
  int y = position.y;
  if (x >= 0 && x < buffer_width && y >= 0 && y < buffer_height) {
    pixel_buffer[y * color_channels * buffer_width + x * color_channels] = color.r;
    pixel_buffer[y * color_channels * buffer_width + x * color_channels + 1] = color.g;
    pixel_buffer[y * color_channels * buffer_width + x * color_channels + 2] = color.b;
    pixel_buffer[y * color_channels * buffer_width + x * color_channels + 3] = color.a;
  }
}

IVec2 NormalOfLine(int x1, int y1, int x2, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int ny = dx;
  int nx = -dy;
  return IVec2{ nx, ny };
}

bool IsPointOnLine(int x, int y, int x1, int y1, int x2, int y2) {
    return (y - y1) * (x2 - x1) == (y2 - y1) * (x - x1);
}


bool IsInRadius(int radius, IVec2 position, int x, int y){
  IVec2 distance = position - IVec2(x,y);
  if (std::sqrt(distance.x * distance.x + distance.y * distance.y) < radius * 2)
    return true;
  return false;
}
