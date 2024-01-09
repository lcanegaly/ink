#include <iostream>
#include "physics_manager.h"
#include "physics.h"
#include "collider.h"

int main(){
  std::cout << "hellow ufcker\n";

  PhysicsManager pm;
  
  Collider* c1 = pm.CreateCollider(glm::vec3(0.0, 0.0, 0.0));
  Collider* c2 = pm.CreateCollider(glm::vec3(0.0, 1.0, 0.0));

  std::cin.get();
  pm.Start();
  std::cin.get();
  pm.Stop(); 
  std::cin.get();
  // Physics physics_;
  // Collider* collider1 = physics.getCollider(sphere, position); 
  // thread d = physics_(run);
  //

  return 0;
}

//in physics run
// for every collider
// collider.checkCollision()
//  if any other object is in collider, apply force to collided, and collidee.
// for every collider
// coliider.updatePosition()
//  take positon and move by force applied.
//
