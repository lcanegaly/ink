#include <emscripten.h>
#include <emscripten/html5.h>
#include "../src/application.h"
#include "../include/ink.h"

#include "client.h"
#include <iostream>
#include <chrono>
#include <memory>

EM_BOOL one_iter(double time, void* userData);

struct AppData {
  std::time_t last;
  std::unique_ptr<Application> app;
};

int main() {
  AppData* app_data = new AppData();
  app_data->last = 0;
  app_data->app = CreateApplication(); 
  emscripten_request_animation_frame_loop(one_iter, (void*)app_data);
  return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  AppData& app_data = *((AppData*)userData);
  std::time_t delta_t = time - app_data.last;
  app_data.last = time;
  app_data.app->Draw();
  app_data.app->Update(delta_t);
  return EM_TRUE;
}

