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
}

void Demo::OnUserUpdate() {
}

void Demo::LoadDemo() {
  ImageView* canvas = new ImageView(Vec2{200,200}, Vec2{290,400});
  canvas->setBrush(Brush(Color{0,255,0}, Stroke()));
  canvas->Point(20, Vec2{100,100}); 
  RegisterObject(canvas);
}

