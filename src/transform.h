#pragma once
#include "glm.hpp"

class Transform2D {
 public:
  glm::vec2 x{1,0};
  glm::vec2 y{0,1};
  glm::vec2 origin{0,0};
};
