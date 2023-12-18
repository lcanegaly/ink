#pragma once
#include <functional>

#include "object.h"
#include "vec2.h"
#include "targa/targa.h"
#include "glm.hpp"

struct Color{
  uint8_t r = 0, g = 0, b = 0, a = 0;
};

struct Stroke{
  int thickness = 1;
};

void SetPixel(unsigned char* pixel_buffer, int buffer_width, 
              int buffer_height, IVec2 position, Color color);
void LineVector(unsigned char* buffer, int width, 
                int height, int x1, int y1, int vx, int vy, int magnitude);
void LineSegment(unsigned char* buffer, int width, int height, 
                 int x1, int y1, int x2, int y2, int thickness);
IVec2 NormalOfLine(int x1, int y1, int x2, int y2);
bool IsPointOnLine(int x, int y, int x1, int y1, int x2, int y2); 
bool IsInRadius(int radius, IVec2 position, int x, int y);

class Brush {
 public:
  Brush() = default;
  Brush(Color color, Stroke stroke):
    color_{color}, stroke_{stroke}{
  }
  Color color(){ return color_; }
  Stroke stroke(){ return stroke_; }
 private:
  Color color_;
  Stroke stroke_;
};

class ImageView : public Object {
 public:
  ImageView(IVec2 size, IVec2 position);
  void Point(int size, IVec2 position); 
  void Line(IVec2 start_point, IVec2 end_point);
  void Draw() override;
  void setBrush(Brush brush); 
  void Clear(Color color = Color{0,0,0,0});
  // TODO - should have functions to get buffer so it can be uploaded as a texture

 private:
  void ForEachPixel(std::function<bool(int,int)> test_condition, 
      std::function<void(int,int)> action);

 private:
  IVec2 size_;
  IVec2 position_;
  PixelBuffer buffer_;
  Brush brush_; 
};
