#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace objimp{

struct Texture{
  float x = 0.0;
  float y = 0.0;
};

struct Point{
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
};

struct Vertex{
  Point Position;
  Texture TexCoord;

  bool operator==(const Vertex& b){
    if (this->Position.x == b.Position.x && this->Position.y == b.Position.y 
        && this->Position.z == b.Position.z && this->TexCoord.x == b.TexCoord.x && this->TexCoord.y == b.TexCoord.y)
      return true;
    return false;
  }
};

struct Face{
  std::vector<unsigned int> vertex_index;
  std::vector<unsigned int> texture_index;
};

// Contains array of points
struct Mesh{
    std::vector<Vertex> Vertices;
    std::vector<int> Indices;
    std::vector<Point> Points;
};

class Model{
 public:
  Model(){}
  Model(const char* filename);
  void print();

 private:
  void CreateMesh();
  bool sort(std::string line);
  
 public:
  std::vector<Mesh> meshes_;
  std::vector<Face> faces_;
  std::vector<Point> points_;
  std::vector<Texture> texture_coords_;
};


}

