#include "../include/ink.h"
#include "bounce.h"
#include <string>
#include <iostream>

std::unique_ptr<Application> CreateApplication(){
  return std::make_unique<Bounce>("bounce", 800, 600);
}

Bounce::Bounce(const char* name, int width, int height) : 
    Application(name, width, height) 
{
  Renderer::Get().SetClearColor(0.25, 0.501, 0.749, 1.0); 
  
  RegisterObject(new Node2D);
  //Load();
}

void Bounce::OnUserUpdate() {}

void Bounce::Load() {
  // Add ball object as the root node for the application.
  RegisterObject(new Ball());
}

Ball::Ball(){
  // Create an ImageView to draw the ball with.
  ImageView* canvas = new ImageView(IVec2{256,256}, IVec2{400,300});
  canvas->Clear();
  canvas->setBrush(Brush(Color{0,255,0,255}, Stroke{2}));
  canvas->Point(50, IVec2{128,128}); 
  // Add the canvas as a child node of ball.
 
  set_position(glm::vec2(10,50), 0);
  Node2D* test = new Node2D;
  test->PushNode(canvas);
  test->transform.origin.x = 50;
  test->transform.origin.y = 50;
  PushNode(test);
}
 
// check and update position if out of bounds. 
void Ball::OnUserUpdate(time_t delta_t) {
 /* 
  // Flip y velocity if past bounds.
  if (position().y > 300 && velocity_.y > 0){
    velocity_.y *= -1.0;
  }else if (position().y < -250 && velocity_.y < 0){
    velocity_.y *= -1.0;
  }
  // Flip x velocity if past bounds.
  if (position().x > 350 && velocity_.x > 0){
    velocity_.x *= -1.0;
  }else if (position().x < -350 && velocity_.x < 0){
    velocity_.x *= -1.0;
  }
  // Update position based on new velocity
  set_position(glm::vec2(position().x + velocity_.x * delta_t, 
        position().y + velocity_.y * delta_t), 0.0);
*/
 } 

