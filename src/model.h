#pragma once
#include "mesh.h"
#include "mesh_renderer.h"
#include "objimp/obj.h"

class Model : public Object {
 public:
   Model(const objimp::Model& model, 
       const Texture& texture, const Shader& shader )
   {} 
};
