#include <emscripten.h>
#include <emscripten/html5.h>
#include "renderer.h"
#include "application.h"
#include "log.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "fractal wasm"

EM_BOOL one_iter(double time, void* userData);

int main()
{
  auto app = CreateApplication(); 
  emscripten_request_animation_frame_loop(one_iter, (void*)app);
  LOG("TEST");
  return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  ((Application*)userData)->Draw();
  ((Application*)userData)->Update();
  return EM_TRUE;
}


