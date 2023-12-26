#include "../include/ink.h"

#include "mesh.h"
#include <iostream>
#include <chrono>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "ink"

int main()
{
  auto startTime = std::chrono::high_resolution_clock::now();
  auto app = CreateApplication();
  auto counter = 0;
  while(!app->shouldClose()) {
    counter++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    startTime = currentTime; 
    app->Draw();
    app->Update(delta_time);
    //if (counter++ > 1000) {
    //  std::cout << "delta = " << delta_time << " \n"; 
    //  counter = 0;
    //} 
  }
  app->Close();
  return 0;
}

