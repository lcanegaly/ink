#pragma once

#include <cmath>
#include <mutex>
#include <iostream>

#include "physics.h"
#include "glm.hpp"
#include "../objimp/obj.h"

enum ColliderMesh {
  sphere = 0, plane
};

class Collider{
  public:
    Collider(double radius, glm::vec3 position); 
    Collider(glm::vec3 position, objimp::Mesh mesh); 
    void SetPosition(glm::vec3 position);
    glm::vec3 OnCollide(Collider& other);
    ColliderMesh collider_mesh_ = ColliderMesh::sphere;
    glm::vec3 sphere_origin = glm::vec3(0);
    double sphere_radius = 1.0;
  private:
    std::mutex collider_lock_;
};

glm::vec3 SphereToSphere(Collider& primary, Collider& other);
