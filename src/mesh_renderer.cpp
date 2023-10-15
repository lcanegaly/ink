#include <gtc/matrix_transform.hpp>
#include "mesh_renderer.h"
#include "renderer.h"
#include "mesh.h"
#include "glm.hpp"

MeshRenderer::MeshRenderer(Mesh& parent_mesh, Shader* shader ) 
    : mesh_{parent_mesh},
      shader_{shader} {
  vao_ = Renderer::Get().VertexArray(); 
  shader_->use(); 
  Renderer::Get().DrawWireframe(false);
}

void MeshRenderer::Load(){}

void MeshRenderer::Draw(){
  mesh_.transform.x.x++;
  glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
	model = glm::rotate(model, glm::radians(glm::degrees(mesh_.transform.x.x)), glm::vec3(1.0f, 0.2f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(40.0f), 800.0f/600.0f, 0.1f, 100.0f);
  model = projection * model; 
  shader_->setMatrix("translate", model); 
  //Renderer::Get().Draw(mesh_.transform, vao_, 36); 
  glBindVertexArray(vao_);  
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

