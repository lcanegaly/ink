#pragma once

#include <cmath>
#include <mutex>
#include <iostream>

#include "physics.h"
#include "glm.hpp"
#include "../objimp/obj.h"
#include "../transform.h"

enum ColliderMeshType {
  sphere = 0, plane, aabb, mesh
};

class Collider{
  public:
    Collider(double radius, glm::vec3 position); 
    Collider(glm::vec3 position, objimp::Mesh mesh); 
    void SetPosition(glm::vec3 position);
    glm::vec3 OnCollide(Collider& other);
    ColliderMeshType collider_mesh_type_ = ColliderMeshType::sphere;
    Transform t;
    double sphere_radius = 1.0;
    objimp::Mesh GetMesh();
    
  private:
    objimp::Mesh collision_mesh;
    std::mutex collider_lock_;
};

glm::vec3 SphereToSphere(Collider& primary, Collider& other);
glm::vec3 SphereToMesh(Collider& sphere, Collider& mesh);

glm::vec3 SupportPointSphere(glm::vec3 position, double radius, glm::vec3 direction);
glm::vec3 SupportPointMesh(glm::vec3 position, objimp::Mesh, glm::vec3 direction);
