#pragma once
#include "object.h"
#include "image.h"
#include "vec2.h"
#include "targa/targa.h"
#include "glm.hpp"

struct Color{
  Color(): red{0},green{255},blue{0}
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
  Color color(){ return color_; }
  Stroke stroke(){ return stroke_; }
 private:
  Color color_;
  Stroke stroke_;
};

class ImageView : public Object {
 public:
  ImageView(Vec2 size, Vec2 position);
  void Point(int size, Vec2 position); 
  void Draw() override;
  void setBrush(Brush brush); 

 private:
  Vec2 size_;
  Vec2 position_;
  Targa::TgaImage* image_; 
  Brush brush_; 
};
