#include "collider.h"
#include "../transform.h"
#include "common.hpp"
#include "ext/quaternion_geometric.hpp"
#include "gtx/norm.hpp"

Collider::Collider(double radius, glm::vec3 position): sphere_radius{radius}, 
  origin{position} 
{ 
  collider_mesh_type_ = ColliderMeshType::sphere;
}
Collider::Collider(glm::vec3 position, objimp::Mesh mesh) 
{
  collision_mesh = mesh;
}   
void Collider::SetPosition(glm::vec3 position) {
  switch (collider_mesh_type_){
    case ColliderMeshType::sphere:
      origin = position;
      break;
    case ColliderMeshType::mesh:
      t.position = position;
      break;
    default:
      std::cout << "No collider support for this type.\n";
  }
}
glm::vec3 Collider::OnCollide(Collider& other){
  switch (collider_mesh_type_){
    case ColliderMeshType::sphere:
      switch (other.collider_mesh_type_){
        case ColliderMeshType::sphere:
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
  glm::vec3 o_mesh = other.origin;
  double o_mesh_radius = other.sphere_radius;
  double t_mesh_radius = primary.sphere_radius;
  glm::vec3 t_mesh = primary.origin;
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

glm::vec3 SphereToMesh(Collider& sphere, Collider& mesh){
  // get direction vector betwen sphere and mesh.
  glm::vec3 direction = sphere.origin - mesh.origin;
  // normalize the vector
  direction = glm::normalize(direction);
  // get sphere support point 1
  glm::vec3 sp1 = SupportPointSphere(sphere.origin, sphere.sphere_radius, direction); 
  // get mesh support point 1
  glm::vec3 mp1 = SupportPointMesh(mesh.origin, mesh.collision_mesh, -direction); 
  // simplex point 1 
  glm::vec3 simplex_1 = sp1 - mp1;
  // get sphere support point 2
  glm::vec3 sp2 = SupportPointSphere(sphere.origin, sphere.sphere_radius, -direction); 
  // get mesh support point 2
  glm::vec3 mp2 = SupportPointMesh(mesh.origin, mesh.collision_mesh, direction);  
  // implex point 2 
  glm::vec3 simplex_2 = sp2 - mp2;
  // check if support point 2 crosses origin.
  // get the dot of the vector that points to origin from original support point, with new support point
  double crosses_origin = glm::dot(-direction, simplex_2); 
  if (crosses_origin < 0)
    return glm::vec3(0);
    //  if not, return 0.
  // get double dot to find support point in direction of origin on both.
  // get a vector that points to origin from second point. get cross product with direction vec
  glm::vec3 up = glm::cross(-simplex_2, -direction); 
  glm::vec3 to_origin = glm::cross(up, -direction);
  // get third simplex
  glm::vec3 sp3 = SupportPointSphere(sphere.origin, sphere.sphere_radius, to_origin); 
  glm::vec3 mp3 = SupportPointMesh(mesh.origin, mesh.collision_mesh, -to_origin);  
  glm::vec3 simplex_3 = sp3 - mp3;
  //  if not past origin, try to find another.
  crosses_origin = glm::dot(-to_origin, simplex_3); 
  if (crosses_origin < 0){
    // try another point towards origin from the trigle side.
    glm::vec3 up = glm::cross(-simplex_3, -to_origin); 
    to_origin = glm::cross(up, -to_origin);
    // get third simplex
    glm::vec3 sp4 = SupportPointSphere(sphere.origin, sphere.sphere_radius, to_origin); 
    glm::vec3 mp4 = SupportPointMesh(mesh.origin, mesh.collision_mesh, -to_origin);  
    glm::vec3 simplex_4 = sp4 - mp4;
    if(simplex_4 == simplex_3)
      return glm::vec3(0); // no new point so return.
    simplex_1 = simplex_4;
    crosses_origin = glm::dot(-to_origin, simplex_1); 
    if (crosses_origin < 0){
      std::cout << "failed to find new triangle point past origin\n";
      return glm::vec3(0);
    }
  }
  // get double dot to find support point to make tetrahedron in direction of origin.
  to_origin = glm::cross(-simplex_1, -simplex_3);
  glm::vec3 sp4 = SupportPointSphere(sphere.origin, sphere.sphere_radius, to_origin); 
  glm::vec3 mp4 = SupportPointMesh(mesh.origin, mesh.collision_mesh, -to_origin);  
  glm::vec3 simplex_4 = sp4 - mp4;
  crosses_origin = glm::dot(-to_origin, simplex_3); 
  if (crosses_origin < 0){
     std::cout << "failed to find simplex point past origin\n";
     return glm::vec3(0);
  }
  std::cout << "is colliding " << 
    simplex_1.x << "," << simplex_1.y << "," << simplex_1.z <<  "\n" << 
    simplex_2.x << "," << simplex_2.y << "," << simplex_2.z <<  "\n" << 
    simplex_3.x << "," << simplex_3.y << "," << simplex_3.z <<  "\n";
  return glm::vec3(1);
}

glm::vec3 SupportPointSphere(glm::vec3 position, double radius, glm::vec3 direction){
  direction = glm::normalize(direction);
  // tranlate the origin to the edge in the direction passed in.
  return position + (glm::vec3(radius) * direction);
}
glm::vec3 SupportPointMesh(glm::vec3 position, objimp::Mesh mesh, glm::vec3 direction){
  direction = glm::normalize(direction);
  glm::vec3 vector_direction = position + direction;
  auto npoint = mesh.Points[0];
  glm::vec3 distance_to_point = glm::vec3(npoint.x - vector_direction.x,
      npoint.y - vector_direction.y, npoint.z - vector_direction.z); 
  for (int i = 0; i < mesh.Points.size(); i++){
    auto point = mesh.Points[i];
    glm::vec3 new_distance_to_point = glm::vec3(point.x - vector_direction.x,
      point.y - vector_direction.y, point.z - vector_direction.z); 
    if (glm::length2(new_distance_to_point) < glm::length2(distance_to_point)){
      npoint = point;
      distance_to_point = new_distance_to_point;
    }
  }
  return glm::vec3(npoint.x, npoint.y, npoint.z);
}
