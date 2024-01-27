#include "collider.h"
#include "../transform.h"
#include "common.hpp"
#include "ext/quaternion_geometric.hpp"
#include "gtx/norm.hpp"
#include <array>

Collider::Collider(double radius, glm::vec3 position): sphere_radius{radius} 
{ 
  collider_mesh_type_ = ColliderMeshType::sphere;
  t.position = position;
}
Collider::Collider(glm::vec3 position, objimp::Mesh mesh) 
{
  collider_mesh_type_ = ColliderMeshType::mesh;
  collision_mesh = mesh;
  t.position = position;
}   
void Collider::SetPosition(glm::vec3 position) {
  t.position = position;
}
glm::vec3 Collider::OnCollide(Collider& other){
  switch (collider_mesh_type_){
    case ColliderMeshType::sphere:
      switch (other.collider_mesh_type_){
        case ColliderMeshType::mesh:
          std::cout << "Colliding a sphere to a mesh\n";
          //return SphereToMesh(*this, other);
          break;
        case ColliderMeshType::sphere:
          return SphereToSphere(*this, other);
          break;
        default:
          std::cout << "No collider to handle this interaction.\n";
          return glm::vec3(0);
      }
    case ColliderMeshType::mesh:
      std::cout << "Colliding a mesh to a mesh\n";
      return MeshToMesh(*this, other);
        break;

  }
  return glm::vec3(0);
}

// Sphere to sphere collider return intersection depth
glm::vec3 SphereToSphere(Collider& primary, Collider& other){
  glm::vec3 o_mesh = other.t.position;
  double o_mesh_radius = other.sphere_radius;
  double t_mesh_radius = primary.sphere_radius;
  glm::vec3 t_mesh = primary.t.position;
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

void print(const char* label, glm::vec3& v){
  std::cout << ">[ " <<  label <<  " ] (" << v.x << ", " << v.y << ", " << v.z <<  ")\n"; 
}


objimp::Mesh Collider::GetMesh(){
  objimp::Mesh m;
  auto mat = t.GlobalMatrix();
  for (auto v : collision_mesh.Points){
    glm::vec4 out = mat * glm::vec4(v.x, v.y, v.z, 1.0);
    auto p = glm::vec3(out.x, out.y, out.z);
    m.Points.push_back(objimp::Point{out.x, out.y, out.z});
  }
  return m; 
}

glm::vec3 MeshToMesh(Collider& mesh, Collider& mesh_other){
  // get direction vector betwen meshes.
  glm::vec3 direction = mesh.t.position - mesh_other.t.position;
  std::vector<glm::vec3> vert;
  
  while (true){
  
    if(vert.size() == 0){
      std::cout << "simplex has no vertices.\n";
      vert.push_back(GetSimplexPoint(mesh, mesh_other, direction)); 
    }
    if(vert.size() == 1){
      std::cout << "simplex has 1 vertex\n";
      vert.push_back(GetSimplexPoint(mesh, mesh_other,-direction));
      if (!PastOrigin(direction, -vert[0])){
        std::cout << "second simplex point not past origin\n";
        return glm::vec3(0); 
      }
    }
    if(vert.size() == 2){
      std::cout << "simplex has 2 vertices\n";
      direction = GetDirection(direction, vert[1]-vert[0]);
      vert.push_back(GetSimplexPoint(mesh, mesh_other, direction));
      if (!PastOrigin(direction, -vert[2])){
        std::cout << "third simplex point not past origin\n";
        glm::vec3 line_ab = vert[1]-vert[0];
        glm::vec3 line_bc = vert[2]-vert[1];
        glm::vec3 line_ca = vert[0]-vert[2];
        glm::vec3 up = glm::cross(line_ab, line_bc); 
        auto ab = glm::dot(up, line_ab);
        auto bc = glm::dot(up, line_bc);
        auto ca = glm::dot(up, line_ca);
        if (ab < bc && ab < ca){
          vert.erase(vert.begin()+2);
        } 
        if (bc < ab && bc < ca){
          vert.erase(vert.begin()+1);
        } 
        if (ca < bc && ca < ab){
          vert.erase(vert.begin()+2);
        }
        direction = GetDirection(up, vert[1]-vert[0]);
        continue;
      }
    }
    if(vert.size() == 3){
      std::cout << "simplex has 3 vertices\n";
      direction = glm::cross(vert[1]-vert[2], vert[0]-vert[1]);
      vert.push_back(GetSimplexPoint(mesh, mesh_other, direction));
      if (!PastOrigin(direction, -vert[3])){
        // Find the closest edge to the origin
        int closestEdge = -1;
        double closestDistance = std::numeric_limits<double>::max();
        glm::vec3 closestDirection;

        for (int i = 0; i < 3; ++i) {
            int j = (i + 1) % 3;
            glm::vec3 edge = vert[j] - vert[i];
            glm::vec3 ao = -vert[i];
            glm::vec3 ab = edge;
            glm::vec3 abPerp = glm::cross(glm::cross(ab, ao), ab);
            
            double distance = glm::length2(ao - glm::dot(ao, ab) / glm::length2(ab) * ab);
            if (distance < closestDistance) {
                closestDistance = distance;
                closestEdge = i;
                closestDirection = abPerp;
            }
        }

        // Reduce the simplex to the closest edge
        int nextVertex = (closestEdge + 1) % 3;
        vert = { vert[closestEdge], vert[nextVertex] };

        // Update the search direction
        direction = closestDirection;

        continue;
      }
    }
  //  get simplex 4 in direction of origin (search dir)
  // if 4 points
    if(vert.size() == 4){
    std::cout << "simplex has 4 vertices\n";
    // Variables to store the closest face information
    int closestFace = -1;
    double closestDistance = std::numeric_limits<double>::max();
    glm::vec3 closestNormal;
    // Check each face
    std::array<std::array<int, 3>, 4> faces = {{{0, 1, 2}, {0, 3, 1}, {1, 3, 2}, {2, 3, 0}}};
    for (const auto& face : faces) {
        glm::vec3 a = vert[face[0]];
        glm::vec3 b = vert[face[1]];
        glm::vec3 c = vert[face[2]];
        glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
        // If the origin is behind this face (toward the normal)
        if (glm::dot(normal, -a) < 0) {
            double distance = glm::length2(glm::cross(b - a, c - a));
            if (distance < closestDistance) {
                closestDistance = distance;
                closestFace = face[0]; // Store the index of the vertex opposite the face
                closestNormal = normal;
            }
        }
    }
    // If closestFace is -1, it means the origin is inside the tetrahedron
    if (closestFace == -1) {
        std::cout << "Collision detected\n";
        break; // Collision detected
    } else {
        // Remove the vertex opposite the closest face
        vert.erase(vert.begin() + closestFace);
        // Update the search direction to the normal of the closest face
        direction = closestNormal;
        continue;
    }
    }
  }
  return glm::vec3(0);
}

glm::vec3 GetDirection(glm::vec3 vec, glm::vec3 vec_other){
  auto up = glm::cross(vec, vec_other);
  auto direction = glm::cross(vec_other,up);
  return glm::normalize(direction);
}

bool PastOrigin(glm::vec3 direction, glm::vec3 point){
  auto check = glm::dot(direction, point);
  if (check > 0){
    return true;
  }
  return false;
}

glm::vec3 GetSimplexPoint(Collider& mesh, Collider& mesh_other, glm::vec3 direction){
  glm::vec3 mp = SupportPointMesh(mesh.t.position, mesh.GetMesh(), direction);
  glm::vec3 mp2 = SupportPointMesh(mesh_other.t.position, mesh.GetMesh(), -direction);
  return mp2 - mp;
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
