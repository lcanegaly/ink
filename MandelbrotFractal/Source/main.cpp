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
//#include "targa.h"


#define WIDTH 800
#define HEIGHT 600

Gui* gui_ptr = nullptr;

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  //printf("screen: (%ld,%ld), client: (%ld,%ld),%s%s%s%s button: %hu, buttons: %hu, movement: (%ld,%ld), target: (%ld, %ld)\n",
  //  e->screenX, e->screenY, e->clientX, e->clientY,
  //  e->ctrlKey ? " CTRL" : "", e->shiftKey ? " SHIFT" : "", e->altKey ? " ALT" : "", e->metaKey ? " META" : "", 
  //  e->button, e->buttons, e->movementX, e->movementY, e->targetX, e->targetY);
  printf("mouse - %ld %ld \n", e->targetX, e->targetY );
  gui_ptr->AddMouseInputEvent(0, 1, (double)e->targetX, (double)e->targetY);  
  return 0;
}


EM_BOOL one_iter(double time, void* userData);
Fractal* fractal_ptr = nullptr;
Renderer* renderer_ptr = nullptr;
MouseInput* mouse_ptr = nullptr;
MouseInput mouse;



int main()
{

  EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("canvas", 0, 1, mouse_callback);
  //EMSCRIPTEN_RESULT ret = emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, 0, 1, mouse_callback);
  Window::Create(WIDTH, HEIGHT);
  renderer_ptr = &Renderer::Get();
  renderer_ptr->Init(WIDTH, HEIGHT, Window::window);
  gui_ptr = new Gui(Renderer::Get());

  fractal_ptr = new Fractal(glm::vec2(WIDTH, HEIGHT), glm::vec2(0.0, 0.0), renderer_ptr);
 

	

  emscripten_request_animation_frame_loop(one_iter, 0);
	//while (!glfwWindowShouldClose(window))
	//while (!Window::ShouldClose())
	//{
		//Window::Clear();

		//fractal.Display();

		//up button
		/*if (gui.Button(40, 40, 80, 80, gui.up_arrow)) 
		{
			fractal.SetBounds(glm::vec2(0.0, 0.1), 0);
		}
		//down button
		if (gui.Button(40, 40, 80, 180, gui.down_arrow))
		{
			fractal.SetBounds(glm::vec2(0.0, -0.1), 0);
		}
		//left button
		if (gui.Button(40, 40, 40, 130, gui.left_arrow))
		{
			fractal.SetBounds(glm::vec2(-0.1, 0.0), 0);
		}
		//right button
		if (gui.Button(40, 40, 120, 130, gui.right_arrow))
		{
			fractal.SetBounds(glm::vec2(0.1, 0.0), 0);
		}
		//zoom in button
		if (gui.Button(40, 40, 160, 80, gui.plus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), 0.1);
		}
		//zoom out button
		if (gui.Button(40, 40, 160, 180, gui.DrawMinus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), -0.1);
		}
		gui.ResetGui();
*/
	//	Window::GetMouseInput(mouse);
	//	gui.AddMouseInputEvent(mouse);
	//}
  //Window::Close();

	return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  
  fractal_ptr->Display();
	//up button
	if (gui_ptr->Button(40, 40, 200, 200, gui_ptr->up_arrow)) 
	{
    printf("button pressed \n");
		fractal_ptr->SetBounds(glm::vec2(0.0, 0.1), 0);
	}
    
  //left button
	if (gui_ptr->Button(40, 40, 40, 130, gui_ptr->down_arrow))
	{
		fractal_ptr->SetBounds(glm::vec2(-0.1, 0.0), 0);
    printf("button pressed \n");
	}


//	gui_ptr->ResetGui();
  return EM_TRUE;
}


