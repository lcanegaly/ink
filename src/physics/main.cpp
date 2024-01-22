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
  //test_sphere_support_point(glm::vec3(0,0,0), 4.0, glm::vec3(0.4,0.5,0.0));
  //test_sphere_support_point(glm::vec3(0,0,0), 4.0, glm::vec3(0.1,0.9,0.0));
  //test_sphere_support_point(glm::vec3(1,1,0), 4.0, glm::vec3(0.4,0.5,0.0));
  //test_sphere_support_point(glm::vec3(0,0,0), 4.0, glm::vec3(1.8,2.4,0.0));

  auto test =  objimp::Model("test.obj");
  auto mesh = test.meshes_[0];
  
  glm::vec3 position = glm::vec3(5.0,0.0,0.0);
  Transform t;
  t.position = position;
  t.angle = 45.0f; 

  for (auto &v : mesh.Points){
    glm::vec4 point = glm::vec4(v.x, v.y, v.z, 1.0); 
    point = t.GlobalMatrix()* point;
    v.x = point.x;
    v.y = point.y;
    v.z = point.z;
    std::cout << v.x << " " << v.y << " " << v.z << "\n";
  }
  std::cout << "\n\n";
  glm::vec3 direction = glm::vec3(1.0, 0.0, 0.0);
  test_mesh_support_point(position, mesh, direction);
}
