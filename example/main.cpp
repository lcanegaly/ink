//#include "dependencies/glew/include/GL/glew.h"
//#include "dependencies/glfw3/include/GLFW/glfw3.h"
#include <emscripten.h>
#include <emscripten/html5.h>
#include "../src/application.h"
#include "../include/ink.h"

#include "demo.h"
#include <iostream>
#include <chrono>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "ink"

EM_BOOL one_iter(double time, void* userData);

int main()
{
  auto startTime = std::chrono::high_resolution_clock::now();
  auto app = CreateApplication(); 

  emscripten_request_animation_frame_loop(one_iter, (void*)app);
  
  //while(!app->shouldClose()) {
        //app->Draw();
    //app->Update(delta_time);
  //}
  //app->Close();
  return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  //auto currentTime = std::chrono::high_resolution_clock::now();
  //auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

  //startTime = currentTime;

  ((Application*)userData)->Draw();
  ((Application*)userData)->Update(time);
  return EM_TRUE;
}

