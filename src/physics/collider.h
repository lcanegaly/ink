#pragma once

#include <cmath>
#include <mutex>
#include <iostream>

#include "physics.h"
#include "glm.hpp"


class Collider{
  public:
    Collider(double radius, glm::vec3 position): sphere_radius{radius}, 
      sphere_origin{position} 
    {}
    void SetPosition(glm::vec3 position) {
      sphere_origin = position; 
    }
    glm::vec3 OnCollide(Collider& other){
      std::lock_guard<std::mutex> lock(collider_lock_);
      glm::vec3 o_mesh = other.sphere_origin;
      double o_mesh_radius = other.sphere_radius;
      double t_mesh_radius = sphere_radius;
      glm::vec3 t_mesh = sphere_origin;
      glm::vec3 diff_vector = o_mesh - t_mesh;
      double d = std::sqrt(
          std::pow((diff_vector.x), 2) + 
          std::pow((diff_vector.y), 2) + 
          std::pow((diff_vector.z), 2));
      if (d != 0 && d <= o_mesh_radius + t_mesh_radius){
        return glm::vec3(diff_vector.x/d, diff_vector.y/d, diff_vector.z/d) * glm::vec3(sphere_radius -d ); 
      }
      return glm::vec3(0);
    }

  private:
    std::mutex collider_lock_;
    glm::vec3 sphere_origin = glm::vec3(0);
    double sphere_radius = 1.0;
};
