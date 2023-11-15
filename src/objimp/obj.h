#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace objimp{
struct Vertex{
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
};

struct Texture{
  double x = 0.0;
  double y = 0.0;
};

struct Face{
  std::vector<unsigned int> vertex_index;
  std::vector<unsigned int> texture_index;
};
struct Mesh{};

class Model{
 public:
  Model(){}
  Model(const char* filename){

    std::size_t file_size = std::filesystem::file_size(filename);
    std::ifstream file = std::ifstream(filename, std::ios::in);
    std::cout << filename << "\n";
    std::string output;
    while (getline(file, output)){
      sort(output);
    }
  }
  void print(){
    for (auto& vert : vertices_){
      printf("vertex - %f %f %f\n", vert.x, vert.y, vert.z);
    }
    for (auto& tex : texture_coords_){
      printf("texture - %f %f\n", tex.x, tex.y);
    }
    for (auto& face : faces_){
      printf("face - %i %i %i\n", face.vertex_index[0], face.vertex_index[1], face.vertex_index[2]);
    }

  }
 private:
  bool sort(std::string line){
    switch(line[0]) {
      case '#':
          //std::cout << line << " line \n";
        break;
      case 'v':
          switch(line[1]){
            case 't': 
              {
                int index = 0;
                Texture t;
                for(size_t i = 0; i < line.length();){
                  auto marker = line.find(' ', i);
                  if (marker != std::string::npos) {
                    auto end = line.find(' ', marker+1);
                    if (end == std::string::npos){
                      end = line.length(); 
                    }
                    i = end; 
                    double* value_ptr = &t.x;
                    std::string out = line.substr(marker+1, end - marker);
                    *(value_ptr + index++) = std::stod(out);
                  }
                }
                texture_coords_.push_back(t); 
              }  
              break;
            case 'n':
              // TODO vertex normals
              break;
            default:
              { 
              int index = 0;
              Vertex v;
              for(size_t i = 0; i < line.length();){
                auto marker = line.find(' ', i);
                if (marker != std::string::npos) {
                  auto end = line.find(' ', marker+1);
                  if (end == std::string::npos){
                    end = line.length(); 
                  }
                  i = end; 
                  double* value_ptr = &v.x;
                  std::string out = line.substr(marker+1, end - marker);
                  *(value_ptr + index++) = std::stod(out);
                }
              }
              vertices_.push_back(v); 
              }
               break;
          }
        break;
        case 'f':
               {
                int index = 0;
                Face f;
                for(size_t i = 0; i < line.length();){
                  auto marker = line.find(' ', i);
                  if (marker != std::string::npos) {
                    auto end = line.find(' ', marker+1);
                    if (end == std::string::npos){
                      end = line.length(); 
                    }
                    i = end; 
                    std::string out = line.substr(marker+1, end - marker);
                    auto face_marker = out.find('/', 0); // find first seperator 
                    std::string face_vert = out.substr(0, face_marker);
                    auto face_end = out.find('/',face_marker+1);// find sec seperator
                    std::string face_tex = ""; 
                    if (face_end == std::string::npos){
                      face_tex = out.substr(face_marker+1, out.length()-face_marker);
                    }else{
                      face_marker = face_end;
                      face_end = out.length();
                      face_tex = out.substr(face_marker+1, face_end - face_marker);
                    }
                    f.vertex_index.push_back(std::stoi(face_vert));
                    f.texture_index.push_back(std::stoi(face_tex));
                  } 
                }
                faces_.push_back(f);
              } 
    }
     
    return true;
    //if first char is f, process faces
    //if first char is m, process mesh
  }
 public:
  std::vector<Mesh> meshes_;
  std::vector<Face> faces_;
  std::vector<Vertex> vertices_;
  std::vector<Texture> texture_coords_;

};


}

