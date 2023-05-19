//#include "dependencies/glew/include/GL/glew.h"
//#include "dependencies/glfw3/include/GLFW/glfw3.h"
#include "../src/application.h"
#include "../include/ink.h"

#include "demo.h"
#include <iostream>
#include <chrono>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "ink"


int main()
{
  auto startTime = std::chrono::high_resolution_clock::now();
  auto frameCount = 0.0;
  
  auto app = CreateApplication(); 

  while(!app->shouldClose()){
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() /1000;
    auto elapsedTime = delta_time /1000;
    frameCount++;

    auto fps = static_cast<double>(frameCount)/elapsedTime;

    if (elapsedTime >= 0.01){
      //std::cout << fps << std::endl;
      startTime = currentTime;
      frameCount = 0;
    }
      app->Draw();
      app->Update(delta_time);
  }
  app->Close();

  return 0;
}

