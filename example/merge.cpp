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
      if (parent){
          parent->transform.angle = (parent->transform.angle < 360.0f) ? parent->transform.angle + 0.4f : 0.4f; 
      }
    }
};

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<Merge>("pup", 1280, 800);
}

Merge::Merge(const char* name, int width, int height) : 
    Application(name, width, height) 
{
  auto& assets = AssetManager::Get();   
  Mesh* floor = new Mesh(&assets.GetShader("texture"), assets.GetModel("floor"), assets.GetTexture("test2"));
  floor->transform.scale = glm::vec3(50.0f, 50.0f, 50.0f);
  RegisterObject(floor);
  
  floor->PushNode(new Ball());

  auto w = 10;
  auto l = 10;
  auto h = 10;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < l; j++){ 
      for (int k = 0; k < h; k++){ 
        Mesh* dog = new Mesh(&AssetManager::Get().GetShader("color"), AssetManager::Get().GetModel("doge"));
        dog->transform.position = glm::vec3( 1.0f + i, 1.0f + k, 1.0f + j);
        dog->transform.scale = glm::vec3( 0.3f, 0.3f, 0.3f);
        dog->set_update_delegate(new EdgeMerge());
        floor->PushNode(dog);
      }
    }
  }
  
  camera_.Position = glm::vec3(0.0f, 150.0f, -100.0f);
  camera_.Translate(camera_.Front, 0.1f);
  GLFWInput::Get().CaptureMouse(true);
  mouse_pos_ = GLFWInput::Get().GetMousePosition();
}

void Merge::OnUserUpdate(std::time_t delta_t) {
  auto mouse_pos = GLFWInput::Get().GetMousePosition();
  auto delta = mouse_pos_ - mouse_pos;
  camera_.Rotate(delta.x * delta_t * -0.005f, delta.y * delta_t * 0.005f); 
  auto key = GLFWInput::Get().GetKey(GLFW_KEY_W);
  if (key){
    camera_.Translate(camera_.Front, 0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_S);
  if (key){
    camera_.Translate(camera_.Front, -0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_A);
  if (key){
    camera_.Translate(camera_.Right, -0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_D);
  if (key){
    camera_.Translate(camera_.Right, 0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_SPACE);
  if (key){
    camera_.Translate(camera_.Up, 0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_X);
  if (key){
    camera_.Translate(camera_.Up, -0.03f * delta_t);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_Z);
  if (key){
    Renderer::Get().Camera()= glm::lookAt(camera_.Position, objects_[0]->transform.position, glm::vec3(0.0,1.0,0.0)); 
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_1);
  if (key){
    GLFWInput::Get().CaptureMouse(true);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_TAB);
  if (key){
    GLFWInput::Get().CaptureMouse(false);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_ESCAPE);
  if (key){
    std::cout << "esc\n"; 
    GLFWInput::Get().CaptureMouse(false);
    Close();
  }
  mouse_pos_ = mouse_pos;
  Renderer::Get().Camera()= camera_.GetViewMatrix(); 
}

void Merge::Load() {
}

Ball::Ball(){ 
  Mesh* dog = new Mesh(&AssetManager::Get().GetShader("color"), AssetManager::Get().GetModel("doge"));
  dog->transform.position = glm::vec3( 0.0f, 1.0f, 0.0f);
  this->transform.rotation_axis = glm::vec3(0, 1, 0 );
  UpdateDelegate* update = new EdgeMerge();
  set_update_delegate(update);
  this->PushNode(dog);
  }
 
void Ball::OnUserUpdate(time_t delta_t) {
} 

