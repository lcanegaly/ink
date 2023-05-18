#include "../include/ink.h"
#include "demo.h"
#include <string>
#include <iostream>

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
  
  ImageView* canvas = new ImageView(Vec2{512,512}, Vec2{300,300});
  canvas->setBrush(Brush(Color{0,255,0}, Stroke{6}));
  canvas->Point(20, Vec2{100,100}); 
  canvas->DrawLine(Vec2{0,100},Vec2{150,200}); 
  canvas->setBrush(Brush(Color{240,2,0}, Stroke{6}));
  canvas->DrawLine(Vec2{150,200},Vec2{300,100}); 
  canvas->setBrush(Brush(Color{0,25,250}, Stroke{6}));
  canvas->DrawLine(Vec2{300,100},Vec2{0,100}); 

  Image* image = new Image("font1.tga", 200,200,200,200);
  Image* image2 = new Image("font1.tga", 200,200,400,200);
  Image* test_image = new Image("font1.tga", 128, 128, 600, 350);
  Button* button = new Button("test.tga", 300,300, 400, 300);
  RegisterObject(canvas);
  RegisterObject(image);
  RegisterObject(image2);
  RegisterObject(test_image);
  RegisterObject(button);
}

