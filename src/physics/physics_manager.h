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
        std::cout << "pm init.. \n";
    }
    RigidBody* CreateRigidBody(glm::vec3 origin, double radius, double mass){
      bodies_.emplace_back(new RigidBody(origin, radius, mass));
      return bodies_[bodies_.size()-1];
    } 
    
    void Start(){
      if (!running_){
        running_ = true;
        std::cout << "pm start.. \n";
        update_thread_ = std::thread (&PhysicsManager::Update, this);
        std::cout << "pm thread start.. \n";
      }
    } 
    void Update(){
      while (true){
        //std::this_thread::sleep_for(std::chrono::milliseconds(1));

        for (auto& b : bodies_){
          Transform bt = b->GetTransform();
          for (auto& b2 : bodies_){
            Transform b2t = b2->GetTransform();
            if (b == b2)
              continue;
            glm::vec3 distance = bt.position - b2t.position;
            if (std::abs(distance.x) > 2.0 || std::abs(distance.y) > 2.0 || std::abs(distance.z) > 2.0)
              continue;
            glm::vec3 intersection = b->Collides(*b2);
            if (intersection != glm::vec3(0)){
              std::cout << "colliding " << bt.position.x << " " 
                << bt.position.z << " with " << b2t.position.x 
                << " " << b2t.position.z << "intersection of " << intersection.x << " " << intersection.z <<  "\n";
              b->ApplyForce(intersection * glm::vec3(1.0));
              b2->ApplyForce(-intersection * glm::vec3(1.0)); }  
          }
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
