#include <gtc/matrix_transform.hpp>
#include "mesh_renderer.h"
#include "renderer.h"
#include "mesh.h"
#include "glm.hpp"

MeshRenderer::MeshRenderer(Mesh& parent_mesh, Shader* shader ) 
    : mesh_{parent_mesh},
      shader_{shader} {
}

void MeshRenderer::Load(){
}

void MeshRenderer::Draw(){
  shader_->use(); 
  vao_ = Renderer::Get().UploadMesh(mesh_.vertex_, mesh_.index_); 
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 projection = Renderer::Get().ProjectionMaxtrix();
  model = projection * mesh_.transform.GlobalMatrix(); 
  shader_->setMatrix("translate", model); 
  
  glBindVertexArray(vao_);  
  glDrawElements(GL_TRIANGLES, mesh_.index_.size(), GL_UNSIGNED_INT, 0);
}

