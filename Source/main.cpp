#include <emscripten.h>
#include <emscripten/html5.h>
#include "renderer.h"
#include "application.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "fractal wasm"

EM_BOOL one_iter(double time, void* userData);

int main()
{
  Application* app = new Application(TITLE, WIDTH, HEIGHT, &Renderer::Get());
  emscripten_request_animation_frame_loop(one_iter, (void*)app);
  return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  ((Application*)userData)->Draw();
  ((Application*)userData)->Update();
  return EM_TRUE;
}


