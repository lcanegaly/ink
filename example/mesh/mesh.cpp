#include "../include/ink.h"
#include "GLFW/glfw3.h"
#include "core/type.hpp"
#include "mesh.h"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include <string>
#include <iostream>
#include "gtc/matrix_transform.hpp"
#include "glm.hpp"

class Spin : public UpdateDelegate {
  public:
    void Update(std::time_t delta_t) override {
      if (parent){
          parent->transform.angle = (parent->transform.angle < 360.0f) ? parent->transform.angle + 0.4f : 0.4f; 
      }
    }
};

class Physx : public UpdateDelegate {
  public:
    Physx(RigidBody* rigidbody) : rigidbody_{rigidbody}{

    }
    void Update(std::time_t delta_t) override {
      if (parent){
          parent->transform.position = rigidbody_->GetTransform().position;
          //std::cout << parent->transform.position.x << parent->transform.position.z << " obj pos \n";
      }
    }
    RigidBody* rigidbody_ = nullptr;
};

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<MeshDemo>("Textured mesh render", 1280, 800);
}

MeshDemo::MeshDemo(const char* name, int width, int height) : 
    Application(name, width, height), camera_{Renderer::Get().GetCamera()}
{
    // Setup demo scene
  Renderer::Get().SetModePerspective();
  auto& assets = AssetManager::Get();  
  Object* world = new Object();
  world->transform.rotation_axis = glm::vec3(0.0f, 1.0f, 0.0f);
  world->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
  RegisterObject(world);
  {
  // Tile floor objects
  auto w = 30;
  auto l = 30;
  auto h = 1;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < l; j++){ 
      for (int k = 0; k < h; k++){ 
          Mesh* floor = new Mesh(&assets.GetShader("texture"), 
              assets.GetModel("floor"), assets.GetTexture("concrete_tile"));
          floor->transform.position = glm::vec3(2 * i, 2 * k, 2 * j);
          world->PushNode(floor);
      }
    }
  }
  } 

  // Draw matrix of mesh
  auto w = 5;
  auto l = 5;
  auto h = 20;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < l; j++){ 
      for (int k = 0; k < h; k++){ 
        RigidBody* c1 = pm_.CreateRigidBody(glm::vec3( 30.0f + i+ k*0.01, 1.0f + k, 30.0f + j), 1.0, 1.0);
        //RigidBody* c1 = pm_.CreateRigidBody(glm::vec3( 30.0f + i + k * 0.01, 1.0f + k, 30.0f + j), 0.5, 1.0);
        Mesh* dog = new Mesh(&AssetManager::Get().GetShader("color"), 
            AssetManager::Get().GetModel("doge"));
        //dog->transform.position = glm::vec3( 1.0f + i, 1.0f + k, 1.0f + j);
        dog->transform.scale = glm::vec3( 0.5f, 0.5f, 0.5f);
        //dog->transform.scale = glm::vec3( 0.3f, 0.3f, 0.3f);
        dog->set_update_delegate(new Physx(c1));
        //dog->set_update_delegate(new Spin());
        world->PushNode(dog);
      }
    }
  }

  /*
  // Setup physics objects.
  RigidBody* c1 = pm_.CreateRigidBody(glm::vec3(30.9, 1.0, 30.0), 1.0, 10.0);
  RigidBody* c2 = pm_.CreateRigidBody(glm::vec3(30.0, 1.0, 30.0), 1.0, 10.0);
  //ram_ = new Mesh(&AssetManager::Get().GetShader("color"), AssetManager::Get().GetModel("doge"));
  //ram_->set_update_delegate(new Physx(c1));
  //world->PushNode(ram_);
  //RigidBody* c2 = pm_.CreateRigidBody(glm::vec3(5.0, 10.0, 5.0), 0.5, 1.0);
  //pm_.Start();
  Mesh* gdog = new Mesh(&AssetManager::Get().GetShader("color"), AssetManager::Get().GetModel("doge"));
  gdog->transform.rotation_axis = glm::vec3(0.0, 1.0, 0.0); 
  gdog->transform.angle = 45.0;
  //gdog->transform.scale = glm::vec3( 0.3f, 0.3f, 0.3f);
  gdog->set_update_delegate(new Physx(c2));
  world->PushNode(gdog);
 
  gdog = new Mesh(&AssetManager::Get().GetShader("color"), AssetManager::Get().GetModel("doge"));
  gdog->transform.rotation_axis = glm::vec3(0.0, 1.0, 0.0); 
  gdog->transform.angle = 45.0;
  gdog->set_update_delegate(new Physx(c1));
  world->PushNode(gdog);
*/ 
  // Position the camera
  camera_.Position = glm::vec3(20.0f, 15.0f, 30.0f);
  camera_.Translate(camera_.Front, 0.1f);
  GLFWInput::Get().CaptureMouse(true);
  mouse_pos_ = GLFWInput::Get().GetMousePosition();
}

void MeshDemo::OnUserUpdate(std::time_t delta_t) {
  // On each update, get mouse position and test for keypresses. 
  auto mouse_pos = GLFWInput::Get().GetMousePosition();
  auto delta = mouse_pos_ - mouse_pos;
  camera_.Rotate(delta.x * delta_t * -0.005f, delta.y * delta_t * 0.005f); 
  //ram_->transform.position = camera_.Position + glm::vec3(0.0, -10.0, 0.0); 
  //std::cout << camera_.Position.x << " " <<  camera_.Position.y << " " << camera_.Position.z << 
   // camera_.Position.r << "\n";
  auto key = GLFWInput::Get().GetKey(GLFW_KEY_W);
  if (key){
    if (GLFWInput::Get().GetKey(GLFW_KEY_LEFT_SHIFT))
      camera_.Translate(camera_.Front, 0.20f * delta_t);
    else
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
  key = GLFWInput::Get().GetKey(GLFW_KEY_1);
  if (key){
    GLFWInput::Get().CaptureMouse(true);
  }
  key = GLFWInput::Get().GetKey(GLFW_KEY_3);
  if (key){
    pm_.Start();
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
}

void MeshDemo::Load() {
}
