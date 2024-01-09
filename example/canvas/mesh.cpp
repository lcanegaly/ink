#include "../include/ink.h"
#include "GLFW/glfw3.h"
#include "core/func_trigonometric.hpp"
#include "core/type.hpp"
#include "mesh.h"
#include "gtc/matrix_transform.hpp"
#include "gtx/transform.hpp"
#include <cmath>
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

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<MeshDemo>("Canvas demo", 1280, 800);
}

MeshDemo::MeshDemo(const char* name, int width, int height) : 
    Application(name, width, height), camera_{Renderer::Get().GetCamera()}
{
  Renderer::Get().SetModePerspective();
  Renderer::Get().SetClearColor(25.0/255.0f, 175.0/255.0f,250.0/255.0f, 1.0f); 
  // Setup demo scene
  auto& assets = AssetManager::Get();  
  Object* world = new Object();
  world->transform.rotation_axis = glm::vec3(0.0f, 1.0f, 0.0f);
  world->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
  world->transform.angle = 0;
  RegisterObject(world);

  // Tile floor objects
  auto w = 3;
  auto l = 3;
  for (int i = 0; i < w; i++){
    for (int j = 0; j < l; j++){ 
        //Mesh* floor = new Mesh(&assets.GetShader("texture"), assets.GetModel("floor"), assets.GetTexture("concrete_tile"));
        //floor->transform.position = glm::vec3(2 * i, 0, 2 * j);
        //world->PushNode(floor);
    }
  }

  Mesh* gate = new Mesh(&assets.GetShader("texture"), assets.GetModel("gate"), assets.GetTexture("gate"));
  gate->transform.position = glm::vec3(0, 1, 0);
  world->PushNode(gate); 
  
  Mesh* line = new Mesh(&assets.GetShader("color"), assets.GetModel("line"));
  line_ = line; 
  line->transform.scale = glm::vec3(0.01, 1.0, 0.1f);
  world->PushNode(line); 

  // Position the camera
  camera_.Position = glm::vec3(0.0f, 10.0f, 0.0f);
  camera_.Rotate(90.0, -90.0, false);
  GLFWInput::Get().CaptureMouse(false);
  mouse_pos_ = GLFWInput::Get().GetMousePosition();
}

void MeshDemo::OnUserUpdate(std::time_t delta_t) {
  // On each update, get mouse position and test for keypresses. 
  auto mouse_pos = GLFWInput::Get().GetMousePosition();
  auto delta = mouse_pos_ - mouse_pos;
  glm::vec2 ndc = Renderer::Get().ScreenToNDC(mouse_pos_, 1280.0f, 800.0f);
  double degree = glm::radians(65.0/2.0);
  double vert = std::tan(degree) * ndc.y;
  double hor = std::tan(degree) * ndc.x * (1280.0/800.0);
  //glm::vec3 nearCenter = camera_.Position - camera_.Front * glm::vec3(1.0);
  //glm::vec3 farCenter = camera_.Position - camera_.Front * glm::vec3(100.0);

  //double nearHeight = 2 * std::tan(glm::radians(65)/ 2) * nearDistance;
  //  real farHeight = 2 * tan(fovRadians / 2) * farDistance;
  //  real nearWidth = nearHeight * viewRatio;
  //  real farWidth = farHeight * viewRatio;
  //line_->transform.position = camera_.Position - glm::vec3(0.0, 1.0, -0.634);
  line_->transform.position = camera_.Position - glm::vec3(-hor, 1.0, -vert);
  //std::cout << ndc.x << " " << ndc.y << " "  <<  camera_.Front.z << "\n";
  std::cout << line_->transform.position.x << " " << line_->transform.position.y  << " "  << line_->transform.position.z << "\n";
  //line_->transform.position = glm::vec3(mouse_pos.y/100.0, 1.0f, -mouse_pos.x/100.0);  
  //camera_.Rotate(delta.x * delta_t * -0.005f, delta.y * delta_t * 0.005f); 
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
  key = GLFWInput::Get().GetKey(GLFW_KEY_2);
  if (key){
    line_->transform.scale = glm::vec3(10.0, 1.0, 0.25f);
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
}

void MeshDemo::Load() {
}
