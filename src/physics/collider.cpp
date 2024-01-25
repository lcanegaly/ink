#include "collider.h"
#include "../transform.h"
#include "common.hpp"
#include "ext/quaternion_geometric.hpp"
#include "gtx/norm.hpp"

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
          return SphereToMesh(*this, other);
          break;
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
  return collision_mesh; 
}



glm::vec3 SphereToMesh(Collider& sphere, Collider& mesh){
  // Copy mesh so we can translate the copy to the correct position
  objimp::Mesh m;
  auto mat = mesh.t.GlobalMatrix();
  for (auto v : mesh.GetMesh().Points){
    glm::vec4 out = mat * glm::vec4(v.x, v.y, v.z, 1.0);
    auto p = glm::vec3(out.x, out.y, out.z);
    m.Points.push_back(objimp::Point{out.x, out.y, out.z});
    print("mesh p",p);
  }
  
  glm::vec3 spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(1,0,0)); 
  print("sphere x", spl); 
  spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(-1,0,0)); 
  print("sphere -x", spl); 
  spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(0,1,0)); 
  print("sphere y", spl); 
  spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(0,-1,0)); 
  print("sphere -y", spl); 
  spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(0,0,1)); 
  print("sphere z", spl); 
  spl = SupportPointSphere(sphere.t.position, sphere.sphere_radius, glm::vec3(0,0,-1)); 
  print("sphere -z", spl); 
  
  // get direction vector betwen sphere and mesh.
  glm::vec3 direction = mesh.t.position - sphere.t.position; 
  print("sphere position", sphere.t.position);
  print("mesh position", mesh.t.position); 
  // normalize the vector
  direction = glm::normalize(direction);
  print("direction", direction);
  // get sphere support point 1
  glm::vec3 sp1 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, direction); 
  print("sp1", sp1);
  // get mesh support point 1
  glm::vec3 mp1 = SupportPointMesh(mesh.t.position, m, -direction); 
  print("mp1", mp1);
  // simplex point 1 
  glm::vec3 simplex_1 = sp1 - mp1;
  print("simplex 1", simplex_1);
  // get sphere support point 2
  glm::vec3 sp2 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, -direction); 
  print("sp2", sp2);
  // get mesh support point 2
  glm::vec3 mp2 = SupportPointMesh(mesh.t.position, m, direction);  
  print("mp2", mp2);
  // implex point 2 
  glm::vec3 simplex_2 = sp2 - mp2;
  print("simplex 2", simplex_2);
  // check if support point 2 crosses origin.
  // get the dot of the vector that points to origin from original support point, with new support point
  glm::vec3 to_origin = -simplex_2;
  
  std::vector<glm::vec3> points;
  double crosses_origin = 0; 
  while (true){
    crosses_origin = glm::dot(-simplex_1, simplex_2); 
    if (crosses_origin < 0){
      std::cout << "simplex2 does not cross origin\n";
      points.push_back(simplex_2);
      to_origin = -simplex_2; 
      glm::vec3 sp2 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
      print("sp2", sp2);
      // get mesh support point 2
      glm::vec3 mp2 = SupportPointMesh(mesh.t.position, m, -to_origin);  
      print("mp2", mp2);
      // implex point 2 
      glm::vec3 new_point_2 = sp2 - mp2;
      for (auto& p : points){
        if (p == new_point_2)
          return glm::vec3(0);
      }
      simplex_2 = new_point_2;
      print("simplex 2", simplex_2);
   
    } else {
      break;
    }
    
  }
  points.clear();
  // get triple cross to find support point in direction of origin on both.
  // get a vector that points to origin from second point. get cross product of direction and up. 
  glm::vec3 up = glm::cross(-simplex_2, direction); 
  print("up", up);
  to_origin = glm::cross(direction, up);
  print("to origin from simplex2", to_origin);
  // get third simplex
  glm::vec3 sp3 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
  print("sp3", sp3);
  glm::vec3 mp3 = SupportPointMesh(mesh.t.position, m, -to_origin);  
  print("mp3", mp3);
  glm::vec3 simplex_3 = sp3 - mp3;
  print("simplex 3", simplex_3);
  //  if not past origin, no collision.
  crosses_origin = glm::dot(-simplex_2, simplex_3); 
  if (crosses_origin < 0){
    std::cout << "simplex3 does not cross origin\n";
    return glm::vec3(0);
  }
 
  // while 2-3 line check fails, remove 1 and get new point in new direction.
  // rename points so 3 is the most recent. 
  // if 2-3 passes break
  while (true){
    // Check if origin is outside of line 2-3.
    // Get normal pointing away from line 2-3 using vector pointing to 3 from 2 triple cross with up.
    glm::vec3 line_2_3 = simplex_3 - simplex_2;
    glm::vec3 line_2_3_out = glm::cross(line_2_3, up);
    print("2-3 vec pointing out", line_2_3_out);
    auto contains = glm::dot(line_2_3_out, simplex_3 ); 
    if (contains < 0){
      std::cout << "line 2-3 doesnt contain origin\n";
      points.push_back(simplex_3);
      // need to try to remove point 1 and  get another point to make a new simplex.
      simplex_1 = simplex_2;
      simplex_2 = simplex_3;
      // get third simplex
      glm::vec3 sp3 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, line_2_3_out); 
      print("sp3", sp3);
      glm::vec3 mp3 = SupportPointMesh(mesh.t.position, m, -line_2_3_out);  
      print("mp3", mp3);
      simplex_3 = sp3 - mp3;
      print("new simplex 3", simplex_3);
      // if new point is the same as the old point, nothing to do return no collide. 
      for (auto& p : points){
        if (p == simplex_3){
          std::cout << "tried to find a new simplex_3 point but couldn't.\n";
          return glm::vec3(0);
        }
      } 
    } else {
      std::cout << "line 2-3 check passes.\n";
      break;
    }
  }
 

  points.clear();
  // while line 1-3 check fails, remove simplex 2 and try to find a new point.
  while (true){
    // Check if origin is outside of line 1-3.
    // Get normal pointing away from 1-3 using vector pointing to 3 from 1 triple cross with up.
    glm::vec3 line_1_3 = simplex_3 - simplex_1;
    glm::vec3 line_1_3_out = glm::cross(-line_1_3, up);
    print("1-3 vec pointing out", line_1_3_out);
   
    auto contains = glm::dot(line_1_3_out, simplex_3 ); 
    if (contains < 0){
      points.push_back(simplex_3);
      std::cout << "line 1-3 does not contain origin\n"; 
      // need to rmove point 2 and find a new point to assign it to. 
      simplex_2 = simplex_1;
      simplex_1 = simplex_3;
      // get third simplex
      glm::vec3 sp3 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, line_1_3_out); 
      print("sp3", sp3);
      glm::vec3 mp3 = SupportPointMesh(mesh.t.position, m, -line_1_3_out);  
      print("mp3", mp3);
      simplex_3 = sp3 - mp3;
      print("new simplex 3", simplex_3);
      // if new point is the same as the old point, nothing to do return no collide. 
      for (auto& p : points){
        if (p == simplex_3){
          std::cout << "tried to find a new simplex_3 point but couldn't.\n";
          return glm::vec3(0);
        }
      }
    } else {
      std::cout << "line 1-3 check passes.\n";
      break;
    }
  }
 
  // If we get here we know triangle does contain origin.
  std::cout << "Tringle does contain origin!\n";


  // Get a point in the direction of origin to make simplex.
  // check each of the three faces to see if origin is outside.
  // while any check fails, try to find a new point in that direction.

  // get double dot to find support point to make terahedron in direction of origin.
  to_origin = glm::cross(-simplex_1, -simplex_3);
 
  // check if to_origin actually points to origin and correct if not.
  auto check = glm::dot(to_origin, -simplex_3);
  if (check < 0)
    to_origin = -to_origin;
 
  print("to origin for 4th point.", to_origin);

  glm::vec3 sp4 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
  glm::vec3 mp4 = SupportPointMesh(mesh.t.position, m, -to_origin);  
  glm::vec3 simplex_4 = sp4 - mp4;
  print("simplex_4", simplex_4);
  crosses_origin = glm::dot(to_origin, simplex_4); 
  if (crosses_origin < 0){
     std::cout << "failed to find simplex point past origin\n";
     return glm::vec3(0);
  }

  // Define starting lines.
  glm::vec3 line_1_4 = simplex_4 - simplex_1;
  glm::vec3 line_2_4 = simplex_4 - simplex_2;
  glm::vec3 line_3_4 = simplex_4 - simplex_3;

  // Check one face of 3, and get a new point if origin not contained in simplex 
  points.clear();
  while (true){
    //check face 1,2,4
    // get normal to face.
    line_1_4 = simplex_4 - simplex_1;
    line_2_4 = simplex_4 - simplex_2;
    
    glm::vec3 face_1_2_4_norm = glm::cross(line_2_4, line_1_4);
    print("face 124 normal", face_1_2_4_norm);
    auto contains = glm::dot(face_1_2_4_norm, -simplex_4); 
    if (contains > 0){
      points.push_back(simplex_4);
      std::cout << "face 124 check does not contain origin\n"; 
      to_origin = face_1_2_4_norm;
      
      glm::vec3 sp4 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
      glm::vec3 mp4 = SupportPointMesh(mesh.t.position, m, -to_origin);  
      glm::vec3 new_point = sp4 - mp4;
      for (auto& p : points){
        if (p == simplex_4){
          std::cout << "tried to find a new simplex_4 point but couldn't.\n";
          return glm::vec3(0);
        }
      }
      crosses_origin = glm::dot(to_origin, simplex_4); 
      if (crosses_origin < 0){
         std::cout << "failed to find simplex point past origin\n";
         return glm::vec3(0);
      }
      simplex_4 = new_point;
    } else {
      std::cout << "face 1 check passed.\n";      
      break; 
    }

  }
  
  // check next face and get a new point if simplex doesn't contain origin.
  while (true){
    //check face 2,3,4
    // get normal to face.
    line_2_4 = simplex_4 - simplex_2;
    line_3_4 = simplex_4 - simplex_3;
    
    glm::vec3 face_2_3_4_norm = glm::cross(line_3_4, line_2_4);
    print("face 234 normal", face_2_3_4_norm);
    auto contains = glm::dot(face_2_3_4_norm, -simplex_4); 
    if (contains > 0){
      std::cout << "face 234 check does not contain origin\n"; 
      to_origin = face_2_3_4_norm;
      
      glm::vec3 sp4 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
      glm::vec3 mp4 = SupportPointMesh(mesh.t.position, m, -to_origin);  
      glm::vec3 new_point = sp4 - mp4;
      if (new_point == simplex_4){
        std::cout << "can't find new fourth simplex point.\n";
        return glm::vec3(0);
      }
      crosses_origin = glm::dot(to_origin, simplex_4); 
      if (crosses_origin < 0){
         std::cout << "failed to find simplex point past origin\n";
         return glm::vec3(0);
      }
      simplex_4 = new_point;
    } else {
      std::cout << "face 2 check passed.\n";      
      break; 
    }
  }


  // check next face and get a new point if simplex doesn't contain origin.
  while (true){
    //check face 3,1,4
    // get normal to face.
    line_1_4 = simplex_4 - simplex_1;
    line_3_4 = simplex_4 - simplex_3;
    
    glm::vec3 face_3_1_4_norm = glm::cross(line_1_4, line_3_4);
    print("face 234 normal", face_3_1_4_norm);
    auto contains = glm::dot(face_3_1_4_norm, -simplex_4); 
    if (contains > 0){
      std::cout << "face 234 check does not contain origin\n"; 
      to_origin = face_3_1_4_norm;
      
      glm::vec3 sp4 = SupportPointSphere(sphere.t.position, sphere.sphere_radius, to_origin); 
      glm::vec3 mp4 = SupportPointMesh(mesh.t.position, m, -to_origin);  
      glm::vec3 new_point = sp4 - mp4;
      if (new_point == simplex_4){
        std::cout << "can't find new fourth simplex point.\n";
        return glm::vec3(0);
      }
      crosses_origin = glm::dot(to_origin, simplex_4); 
      if (crosses_origin < 0){
         std::cout << "failed to find simplex point past origin\n";
         return glm::vec3(0);
      }
      simplex_4 = new_point;
    } else {
      std::cout << "face 3 check passed.\n";      
      break; 
    }
  }
  // If we get here.. we are colliding.
  std::cout << "colliding, so sphere point should be past mesh point.\n";
  print("collision direction is: ", direction);
  glm::vec3 sfp = SupportPointSphere(sphere.t.position, sphere.sphere_radius,direction); 
  glm::vec3 scp = SupportPointSphere(sphere.t.position, sphere.sphere_radius, -direction); 
  glm::vec3 mfp = SupportPointMesh(mesh.t.position, m, -direction);  
  glm::vec3 mcp = SupportPointMesh(mesh.t.position, m, direction);  

  print("sphere furthest point", sfp);
  print("sphere closest point", scp);
  print("mesh furthest point", mfp);
  print("mesh closest point", mcp);
  return glm::vec3(1);
}

glm::vec3 SupportPointSphere(glm::vec3 position, double radius, glm::vec3 direction){
  direction = glm::normalize(direction);
  // tranlate the origin to the edge in the direction passed in.
  return position + (glm::vec3(radius) * direction);
}
glm::vec3 SupportPointMesh(glm::vec3 position, objimp::Mesh mesh, glm::vec3 direction){
  //direction = glm::normalize(direction);
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
