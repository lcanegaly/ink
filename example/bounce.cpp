#include "../include/ink.h"
#include "bounce.h"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
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
  RegisterObject(world);
  
  world->PushNode(new Ball());
  camera_.Position = glm::vec3(0.0f, 0.0f, 8.0f);
}

void Bounce::OnUserUpdate() {
   
  auto key = GLFWInput::Get().GetKey(GLFW_KEY_W);
  if (key){
    camera_.Translate(glm::vec3(0.0f, 0.0f, 0.1f), 0.1f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_S);
  if (key){
    camera_.Translate(glm::vec3(0.0f, 0.0f, -0.1f), 0.1f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_A);
  if (key){
    camera_.Translate(glm::vec3(0.1f, 0.0f, 0.0f), 0.1f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_D);
  if (key){
    camera_.Translate(glm::vec3(-0.1f, 0.0f, 0.0f), 0.1f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_Q);
  if (key){
    camera_.Rotate(-0.1f, 0.0f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_E);
  if (key){
    std::cout << camera_.Yaw << "\n";
    camera_.Rotate(0.1f, 0.0f); 
    Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  }
}

void Bounce::Load() {
  // Add ball object as the root node for the application.
}

Ball::Ball(){ 
  Shader* shader = new Shader("/home/lee/code/ink/build/vertex.sh",
      "/home/lee/code/ink/build/fragment.sh");
  Mesh* dog = new Mesh(shader, "/home/lee/code/ink/build/test.obj");
  dog->transform.scale = glm::vec3( 0.01f, 0.01f, 0.01f);
  this->transform.rotation_axis = glm::vec3(0, 1, 0 );
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

