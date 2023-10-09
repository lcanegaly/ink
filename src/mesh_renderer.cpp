#include "mesh_renderer.h"
#include "renderer.h"
#include "mesh.h"

MeshRenderer::MeshRenderer(Mesh& parent_mesh) : mesh_{parent_mesh}{
  vao_ = Renderer::Get().VertexArray(); 
  Renderer::Get().LoadShader();
  Renderer::Get().DrawWireframe(true);
}
void MeshRenderer::Load(){}
void MeshRenderer::Draw(){
  mesh_.transform.x.x++;
  Renderer::Get().Draw(mesh_.transform, vao_, 36); 
}

