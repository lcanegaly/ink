#pragma once
#include <functional>

#include "object.h"
#include "image.h"
#include "vec2.h"
#include "targa/targa.h"
#include "glm.hpp"

//TODO - update these functions to take Vec2 and Color
void SetPixel(unsigned char* pixel_buffer, int buffer_width, 
              int buffer_height, int x, int y, uint8_t r, uint8_t g, uint8_t b);
void SetPixel(unsigned char* pixel_buffer, int buffer_width, 
              int buffer_height, int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void LineVector(unsigned char* buffer, int width, 
                int height, int x1, int y1, int vx, int vy, int magnitude);
void LineSegment(unsigned char* buffer, int width, int height, 
                 int x1, int y1, int x2, int y2, int thickness);
IVec2 NormalOfLine(int x1, int y1, int x2, int y2);
bool IsPointOnLine(int x, int y, int x1, int y1, int x2, int y2); 
bool IsInRadius(int radius, IVec2 position, int x, int y);

struct Color{
  uint8_t r, g, b;
};

struct Stroke{
  int thickness;
};

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
  void DrawLine(IVec2 start_point, IVec2 end_point);
  void Draw() override;
  void setBrush(Brush brush); 
  void Clear();

 private:
  void ForEachPixel(std::function<bool(int,int)> test_condition, 
      std::function<void(int,int)> action);

 private:
  IVec2 size_;
  IVec2 position_;
  PixelBuffer buffer_;
  Brush brush_; 
};
