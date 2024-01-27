#include <iostream>
#include "collider.h"

void test_sphere_support_point(glm::vec3 position, double radius, glm::vec3 direction){
  glm::vec3 sphere_point = SupportPointSphere(position, radius, direction);
  std::cout << "sphere support point = " << sphere_point.x << ", " << sphere_point.y << ", " << sphere_point.z << "." << "\n";
}

void test_mesh_support_point(glm::vec3 position, objimp::Mesh mesh, glm::vec3 direction){
  glm::vec3 mesh_point = SupportPointMesh(position, mesh, direction);
  std::cout << "mesh support point = " << mesh_point.x << ", " << mesh_point.y << ", " << mesh_point.z << "." << "\n";
}

int main(){

  auto test =  objimp::Model("test.obj");
  auto mesh = test.meshes_[0];
  
  Collider mcollider = Collider(glm::vec3(0.0,0.0,0.0), mesh);
  Collider m2collider = Collider(glm::vec3(2.0,0.0,0.0), mesh);
  //Collider scollider = Collider(0.5, glm::vec3(1.3, 0, 0));
 
  //auto collision = scollider.OnCollide(mcollider);
  auto collision = mcollider.OnCollide(m2collider);
  std::cout << collision.x << " " << collision.y << " " << collision.z << "\n"; 
}
