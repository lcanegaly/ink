#include "../include/ink.h"
#include "core/type.hpp"
#include "merge.h"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include <string>
#include <iostream>
#include "gtc/matrix_transform.hpp"
#include "glm.hpp"

class EdgeMerge : public UpdateDelegate {
  public:
    void Update(std::time_t delta_t) override {
      if (parent)
        parent->transform.angle = parent->transform.angle + 0.1f; 
    }
};

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<Merge>("pup", 1280, 1024);
}

Merge::Merge(const char* name, int width, int height) : 
    Application(name, width, height) 
{
    
  Renderer::Get().SetClearColor(0.25, 0.501, 0.749, 1.0); 
 
  Shader* shader = new Shader("/home/lee/code/ink/build/tex_vertex.sh",
      "/home/lee/code/ink/build/tex_fragment.sh");
  shader->setInt("tex", 0);
  //Mesh* floor = new Mesh(shader, "/home/lee/code/ink/build/floor.obj");
  //floor->texture_ = new Targa::TgaImage("/home/lee/code/ink/build/test.tga");
  //floor->tex_ = Renderer::Get().LoadTexture((unsigned char*)floor->texture_->data(), 1, floor->texture_->width(),floor->texture_->height(), 4); 

  //floor->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
  //floor->transform.position.y = -0.1f;
  //RegisterObject(floor);
  
  //floor->PushNode(new Ball());
  Mesh* test = new Mesh(shader, "/home/lee/code/ink/build/quad2.obj"); 
  test->texture_ = new Targa::TgaImage("/home/lee/code/ink/build/brick.tga");
  test->tex_ = Renderer::Get().LoadTexture((unsigned char*)test->texture_->data(), 0, test->texture_->width(),test->texture_->height(), 4); 
  test->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
  RegisterObject(test);
  camera_.Position = glm::vec3(0.0f, 50.0f, 0.0f);
  camera_.Translate(camera_.Front, 0.1f);
  GLFWInput::Get().CaptureMouse(true);
  mouse_pos_ = GLFWInput::Get().GetMousePosition();

}

void Merge::OnUserUpdate(std::time_t delta_t) {
  auto mouse_pos = GLFWInput::Get().GetMousePosition();
  auto delta = mouse_pos_ - mouse_pos;
  camera_.Rotate(delta.x * delta_t * -0.001f, delta.y * delta_t * 0.001f); 
  auto key = GLFWInput::Get().GetKey(GLFW_KEY_W);
  if (key){
    camera_.Translate(camera_.Front, 0.1f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_S);
  if (key){
    camera_.Translate(camera_.Front, -0.1f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_A);
  if (key){
    camera_.Translate(camera_.Right, -0.01f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_D);
  if (key){
    camera_.Translate(camera_.Right, 0.01f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_SPACE);
  if (key){
    camera_.Translate(camera_.Up, 0.01f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_X);
  if (key){
    camera_.Translate(camera_.Up, -0.01f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_ESCAPE);
  if (key){
    std::cout << "esc\n"; 
    GLFWInput::Get().CaptureMouse(false);
    Close();
  }
  mouse_pos_ = mouse_pos;
  //Renderer::Get().Camera()= camera_.GetViewMatrix(); 
  Renderer::Get().Camera()= glm::lookAt(camera_.Position, objects_[0]->transform.position, glm::vec3(0.0,1.0,0.0)); 
}

void Merge::Load() {
  // Add ball object as the root node for the application.
}

Ball::Ball(){ 
  Shader* shader = new Shader("/home/lee/code/ink/build/vertex.sh",
      "/home/lee/code/ink/build/fragment.sh");
  Mesh* dog = new Mesh(shader, "/home/lee/code/ink/build/test.obj");
  dog->transform.position = glm::vec3( 0.0f, 1.5f, 0.0f);
  this->transform.rotation_axis = glm::vec3(0, 1, 0 );
  UpdateDelegate* update = new EdgeMerge();
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

