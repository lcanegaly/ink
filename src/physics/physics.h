#pragma once
#include <iostream>
#include <mutex>
#include "glm.hpp"

class Mass {
  public:
    Mass(double mass): mass_{mass}{}
    void ApplyForce(const glm::vec3& applied_force) {
      std::lock_guard<std::mutex> lock(physics_lock_);
      force_ += applied_force;
    }
    glm::vec3 Update(std::time_t timestep){
      std::lock_guard<std::mutex> lock(physics_lock_);
      double timestepSeconds = timestep / 1000.0;
      if (force_ == glm::vec3(0.0))
        return velocity_; 
      glm::vec3 acceleration = force_ / glm::vec3(mass_);
      velocity_ += acceleration * glm::vec3(timestepSeconds);
      // Apply damping (adjust dampingFactor as needed)
      double dampingFactor = 0.5; // Example value
      velocity_ *= dampingFactor;
      // Reset force for the next update
      force_ = glm::vec3(0.0);
      std::cout << velocity_.x << velocity_.y << velocity_.z << "\n"; 
      return velocity_;
    } 
    glm::vec3 Velocity(){
      std::lock_guard<std::mutex> lock(physics_lock_);
      return velocity_;
    }
  private:
    std::mutex physics_lock_;
    double mass_ = 0.01;
    glm::vec3 velocity_ = glm::vec3(0.0);
    glm::vec3 force_ = glm::vec3(0.0);
};


