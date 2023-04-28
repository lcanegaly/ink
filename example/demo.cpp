#include "../include/ink.h"
#include "demo.h"
#include <string>

Application* CreateApplication(){
  return new Demo("demo app", 800, 600);
}

Demo::Demo(const char* name, int width, int height) : 
    Application(name, width, height) 
{
  Renderer::Get().SetClearColor(0.25, 0.501, 0.749, 1.0); 
  LoadDemo();
  //std::cout << "loading demo ]\n";
  }

void Demo::OnUserUpdate() {
}

void Demo::LoadDemo() {
  
  Image* fan = new Image("fan.tga", &Renderer::Get(), 125, 125, 535, 180 );
  RegisterObject(fan);

}

