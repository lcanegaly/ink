#include <emscripten.h>
#include <emscripten/html5.h>
#include "Window.h"
#include <iostream>
#include "Renderer.h"
#include "Shaders.h"
#include "Fractal.h"
#include "Gui.h"
#include "MouseInput.h"
#include "glm.hpp"

#define WIDTH 800
#define HEIGHT 600

Gui* gui_ptr = nullptr;
EM_BOOL one_iter(double time, void* userData);
Fractal* fractal_ptr = nullptr;
Renderer* renderer_ptr = nullptr;
MouseInput* mouse_ptr = nullptr;
MouseInput mouse;

//Application application(WIDTH, HEIGHT);

void checkInput(){

  //up button
	if (gui_ptr->Button(40, 40, 80, 80, gui_ptr->up_arrow)) 
	{
		fractal_ptr->SetBounds(glm::vec2(0.0, 0.1), 0);
	}
 /* 
  //down
	if (gui_ptr->Button(40, 40, 80, 180, gui_ptr->down_arrow))
	{
		fractal_ptr->SetBounds(glm::vec2(0.0, -0.1), 0);
	}
	
  //left button
	if (gui_ptr->Button(40, 40, 40, 130, gui_ptr->left_arrow))
	{
	  fractal_ptr->SetBounds(glm::vec2(-0.1, 0.0), 0);
	}
	//right button
	if (gui_ptr->Button(40, 40, 120, 130, gui_ptr->right_arrow))
	{
		fractal_ptr->SetBounds(glm::vec2(0.1, 0.0), 0);
	}
	//zoom in button
	if (gui_ptr->Button(40, 40, 160, 80, gui_ptr->plus))
	{
		fractal_ptr->SetBounds(glm::vec2(0.0, 0.0), 0.1);
	}
	//zoom out button
	if (gui_ptr->Button(40, 40, 160, 180, gui_ptr->minus))
	{
		fractal_ptr->SetBounds(glm::vec2(0.0, 0.0), -0.1);
	}
  */
}


EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  gui_ptr->AddMouseInputEvent(0, 1, (double)e->targetX, (double)e->targetY);  
  return 0;
}

int main()
{
  EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("canvas", 0, 1, mouse_callback);
  //EMSCRIPTEN_RESULT ret = emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, 0, 1, mouse_callback);
  Window::Create(WIDTH, HEIGHT);
  renderer_ptr = &Renderer::Get();
  renderer_ptr->Init(WIDTH, HEIGHT, Window::window);
  gui_ptr = new Gui(Renderer::Get());
  fractal_ptr = new Fractal(glm::vec2(WIDTH, HEIGHT), glm::vec2(0.0, 0.0), renderer_ptr);


  emscripten_request_animation_frame_loop(one_iter, (void*)fractal_ptr);

	return 0;
}

EM_BOOL one_iter(double time, void* userData) {

  Fractal* ptr =(Fractal*)userData;
  ptr->Display();
  //fractal_ptr->Display();
  checkInput();
//	gui_ptr->ResetGui();
  return EM_TRUE;
}


