#pragma once
#include <vector>
#include <algorithm>

#include "object.h"
#include "mesh_renderer.h"
#include "glm.hpp"
#include "objimp/obj.h"
#include "targa/targa.h"
#include "vertex.h"
     
// TODO - a model would have many meshes and possibly materials.
class Mesh : public Object {
 public:
  Mesh(Shader* shader, objimp::Model model)
          : Object(new NoUpdate, new MeshRenderer(*this, shader)), model_{model}{
    // TODO this is loading texture coords wrong.

    for (int i = 0; i < model_.faces_.size(); i++) {
      for (int j = 0; j < model_.faces_[i].vertex_index.size(); j++) {
        //for each face, push the vertex and texture indices values to a Vertex struct
        Vertex v;
        auto face_index = model_.faces_[i].vertex_index[j] - 1;
        auto face_tex = model_.faces_[i].texture_index[j] - 1;
        auto vertex = model_.vertices_[face_index]; 
        auto texture_coord = model_.texture_coords_[face_tex]; 
        v.Position = {(float)vertex.x, (float)vertex.y, (float)vertex.z};
        v.TexCoords = {(float)texture_coord.x, (float)texture_coord.y};
        if (findVertex(v) == -1){
          vertices_.push_back(v); 
          index_.push_back(vertices_.size() -1); // index starting at 1
        } else {
          index_.push_back(findVertex(v)); 
        }
      }
    }
  }
  int findVertex(Vertex v){
    for (int i = 0; i < vertices_.size(); i++){
      auto vert = vertices_[i];
      if (vert.Position.x == v.Position.x &&
          vert.Position.y == v.Position.y &&
          vert.Position.z == v.Position.z && 
          vert.TexCoords.x == v.TexCoords.x &&
          vert.TexCoords.y == v.TexCoords.y){
          return i;
      }
    } 
    return -1;
  }
  GLuint tex_ = 0;
  Targa::TgaImage* texture_ = nullptr;
  objimp::Model model_;
  std::vector<Vertex> vertices_;
  std::vector<unsigned int> index_;
  void OnUserUpdate(std::time_t delta_t) override {
  }
};



