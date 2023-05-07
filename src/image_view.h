#pragma once
#include "object.h"
#include "image.h"
#include "vec2.h"

struct Color{
  Color(): red{255},green{0},blue{0}
  {}
  int red;
  int green;
  int blue;
};

struct Stroke{
  Stroke():thickness{1}
  {} 
  int thickness;
};

class Brush {
 public:
  Brush() = default;
  Brush(Color color, Stroke stroke):
    color_{color}, stroke_{stroke}{
  }
 private:
  Color color_;
  Stroke stroke_;
};

class ImageView : public Object {
 public:
  ImageView(Vec2 size, Vec2 pos);
  void Point(int size, Vec2 pos);
  void Draw() override;
  

 private:
  Image image_;
  Brush brush_; 
};
