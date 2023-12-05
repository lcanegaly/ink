#pragma once

#include "glm.hpp"
struct Vertex {
  struct {
    float x;
    float y;
    float z;
  } Position;

  struct  {
    float x;
    float y;
  } TexCoords;

  bool operator==(const Vertex& b){
    if (this->Position.x == b.Position.x && this->Position.y == b.Position.y 
        && this->Position.z == b.Position.z && this->TexCoords.x == b.TexCoords.x && this->TexCoords.y == b.TexCoords.y)
      return true;
    return false;
  }
};
 
