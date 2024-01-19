#pragma once

#include <chrono>
#include <vector>
#include <thread>
#include <iostream>
#include <mutex>

#include "physics.h"
#include "rigid_body.h"

class PhysicsManager{
  public:
    PhysicsManager(){
    }
    RigidBody* CreateRigidBody(glm::vec3 origin, double radius, double mass){
      bodies_.emplace_back(new RigidBody(origin, radius, mass));
      return bodies_[bodies_.size()-1];
    } 
    
    void Start(){
      if (!running_){
        running_ = true;
        update_thread_ = std::thread (&PhysicsManager::Update, this);
      }
    } 
    void Update(){
      while (true){
        for (auto& b : bodies_){
          Transform bt = b->GetTransform();
          for (auto& b2 : bodies_){
            Transform b2t = b2->GetTransform();
            // If comparing the same rigidbody skip.
            if (b == b2)
              continue;
            // Get distance vector between transforms
            glm::vec3 distance = bt.position - b2t.position;
            // If rigidbodies are not close skip
            if (std::abs(distance.x) > 2.0 || std::abs(distance.y) > 2.0 
                || std::abs(distance.z) > 2.0)
              continue;
            // Get a intersection vector from collision check.
            glm::vec3 intersection = b->Collides(*b2);
            // if intersection is not 0, collision has occured.
            if (intersection != glm::vec3(0)){
              // Apply equal force proportional to intersection depth to each 
              // object.
              b->ApplyForce(intersection * glm::vec3(1.0));
              b2->ApplyForce(-intersection * glm::vec3(1.0)); }  
          }
        // Apply gravity to body
        b->ApplyForce(glm::vec3(0.0, -9.8, 0.0));
        b->Update(timestep_); 
        }
        std::lock_guard<std::mutex> lock(physics_manager_lock_);
        if (!running_){
          break;
        }
      }
    }

    void Stop(){
      std::lock_guard<std::mutex> lock(physics_manager_lock_);
      running_ = false;
    }
    ~PhysicsManager(){
      if (update_thread_.joinable())
        update_thread_.join(); 
    }


  private:
    std::time_t timestep_ = 1000/30;
    bool running_ = false;;
    std::mutex physics_manager_lock_;
    std::vector<RigidBody*> bodies_;;
    std::thread update_thread_;
};
