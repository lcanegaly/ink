#include "collider.h"

Collider::Collider(double radius, glm::vec3 position): sphere_radius{radius}, 
  sphere_origin{position} 
{ 
  collider_mesh_ = ColliderMesh::sphere;
}
Collider::Collider(glm::vec3 position, objimp::Mesh mesh) 
{
}   
void Collider::SetPosition(glm::vec3 position) {
  sphere_origin = position; 
}
glm::vec3 Collider::OnCollide(Collider& other){
  //std::lock_guard<std::mutex> lock(collider_lock_);
  switch (collider_mesh_){
    case ColliderMesh::sphere:
      switch (other.collider_mesh_){
        case ColliderMesh::sphere:
          return SphereToSphere(*this, other);
          break;
        default:
          std::cout << "No collider to handle this interaction.\n";
          return glm::vec3(0);
      }
  }
  return glm::vec3(0);
}

// Sphere to sphere collider return intersection depth
glm::vec3 SphereToSphere(Collider& primary, Collider& other){
  glm::vec3 o_mesh = other.sphere_origin;
  double o_mesh_radius = other.sphere_radius;
  double t_mesh_radius = primary.sphere_radius;
  glm::vec3 t_mesh = primary.sphere_origin;
  glm::vec3 diff_vector = o_mesh - t_mesh;
  double d = std::sqrt(
      std::pow((diff_vector.x), 2) + 
      std::pow((diff_vector.y), 2) + 
      std::pow((diff_vector.z), 2));
  if (d != 0 && d <= o_mesh_radius + t_mesh_radius){
    return glm::vec3(diff_vector.x/d, diff_vector.y/d, diff_vector.z/d) * glm::vec3(primary.sphere_radius - d); 
  }
  return glm::vec3(0);
}

