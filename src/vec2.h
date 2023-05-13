#pragma once

struct Vec2 {
  //Vec2(int x_pos, int y_pos)
  //: x{x_pos}, y{y_pos}
  //{}
  Vec2 operator-(Vec2 other){
    return Vec2{x-other.x, y-other.y};
  }  
  int x;
  int y;
};


