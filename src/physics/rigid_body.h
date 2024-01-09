#pragma once

#include "physics.h"
#include "collider.h"
#include "../transform.h"
#include <mutex>

class RigidBody{
  public:
    RigidBody(glm::vec3 position, double radius, double mass): mass_{Mass(mass)}{
      collider_ = new Collider(radius, position); 
      transform.position = position;
    }
    void ApplyForce(glm::vec3 force){
      mass_.ApplyForce(force);
    }
    glm::vec3 Collides(RigidBody& other){
      std::lock_guard<std::mutex> lock(rigidbody_lock_); 
      glm::vec3 result_force = collider_->OnCollide(*other.collider_);
      if (std::abs(result_force.x) > 0 || std::abs(result_force.z) > 0) 
        std::cout << result_force.x << " " << result_force.z << "result force\n";
      return result_force;
    }
    void Update(time_t timestep){
      std::lock_guard<std::mutex> lock(rigidbody_lock_); 
      std::cout << "pos: " << transform.position.x << " " << transform.position.y << " " << transform.position.z << "\n";
      mass_.Update(timestep);
      transform.position += mass_.Velocity() * glm::vec3(timestep);
      if (transform.position.y < 0)
        transform.position.y = 0.0;
      collider_->SetPosition(transform.position);
    }
    Transform GetTransform() {
      std::lock_guard<std::mutex> lock(rigidbody_lock_); 
      return transform; 
    }
  private:
    Transform transform;
    std::mutex rigidbody_lock_; 
    Mass mass_; 
    Collider* collider_;
};