#pragma once
#include <vector>
#include <algorithm>

#include "object.h"
#include "mesh_renderer.h"
#include "glm.hpp"
#include "objimp/obj.h"
#include "targa/targa.h"

// TODO - a model would have many meshes and possibly materials.
class Mesh : public Object {
 public:
  Mesh(Shader* shader, objimp::Model model)
          : Object(new NoUpdate, new MeshRenderer(*this, shader)), model_{model}{
    int vertex_count = 3; 
    int texture_coord_count = 2;
    for (int i = 0; i < model_.vertices_.size(); i++){
      for(int j = 0; j < vertex_count; j++){ 
        vertex_.push_back(
          *((&model_.vertices_[i].x)+j)); // Accessing struct members by offset
    }
      for(int j = 0; j < texture_coord_count; j++) { 
        vertex_.push_back(
          *((&model_.texture_coords_[i].x)+j)); // Accessing struct members by offset
      } 
    }
    for (int i = 0; i < model_.faces_.size(); i++){
      for (int j = 0; j < model_.faces_[i].vertex_index.size(); j++) {
        index_.push_back(model_.faces_[i].vertex_index[j] - 1); // index starting at 1
      }
    }
  }
  GLuint tex_ = 0;
  Targa::TgaImage* texture_ = nullptr;
  objimp::Model model_;
  std::vector<float> vertex_;
  std::vector<unsigned int> index_;
  void OnUserUpdate(std::time_t delta_t) override {
  }
};



