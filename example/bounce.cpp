#include "../include/ink.h"
#include "bounce.h"
#include <string>
#include <iostream>

class EdgeBounce : public UpdateDelegate {
  public:
    void Update(std::time_t delta_t) override {
      if (parent)
        parent->transform.angle = parent->transform.angle + 0.1f; 
    }
};

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<Bounce>("pup", 800, 600);
}

Bounce::Bounce(const char* name, int width, int height) : 
    Application(name, width, height) 
{
    
  Renderer::Get().SetClearColor(0.25, 0.501, 0.749, 1.0); 
 
  Shader* shader = new Shader("/home/lee/code/ink/build/vertex.sh",
      "/home/lee/code/ink/build/fragment.sh");

  Object* world = new Object();
  world->transform.rotation_axis = glm::vec3(0, 1, 0);
  world->transform.position.z = -300.0f;
  world->transform.angle = 90.0f;
  RegisterObject(world);
  
  world->PushNode(new Ball());
  //Load();
}

void Bounce::OnUserUpdate() {

}

void Bounce::Load() {
  // Add ball object as the root node for the application.
}

Ball::Ball(){ 
  Shader* shader = new Shader("/home/lee/code/ink/build/vertex.sh",
      "/home/lee/code/ink/build/fragment.sh");
  Mesh* dog = new Mesh(shader, "/home/lee/code/ink/build/test.obj");
  UpdateDelegate* update = new EdgeBounce();
  update->parent = this;
  //set_updateDelegate(update);
  this->PushNode(dog);
}
 
void Ball::OnUserUpdate(time_t delta_t) {
/* 
  // Flip y velocity if past bounds.
  if (transform.position.y > 4 && velocity_.y > 0){
    velocity_.y *= -1.0;
  }else if (transform.position.y < -4 && velocity_.y < 0){
    velocity_.y *= -1.0;
  }
  // Flip x velocity if past bounds.
  if (transform.position.x > 4 && velocity_.x > 0){
    velocity_.x *= -1.0;
  }else if (transform.position.x < -4 && velocity_.x < 0){
    velocity_.x *= -1.0;
  }
  // Update position based on new velocity
  transform.position.x  = transform.position.x  + velocity_.x * delta_t; 
  transform.position.y  = transform.position.y  + velocity_.y * delta_t; 
*/
  } 

