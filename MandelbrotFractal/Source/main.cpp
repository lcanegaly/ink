//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
//#include "Window.h"
#include <iostream>
#include "Renderer.h"
#include "Shaders.h"
#include "Fractal.h"
#include "Gui.h"
//#include "MouseInput.h"
#include "glm.hpp"


#define WIDTH 800
#define HEIGHT 600

EM_BOOL one_iter(double time, void* userData);
Fractal* fractal_ptr = nullptr;
Renderer* renderer_ptr = nullptr;
Gui* gui_ptr = nullptr;

int main()
{

  renderer_ptr = &Renderer::Get();
  renderer_ptr->Init(WIDTH, HEIGHT);
 
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

	return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  // Can render to the screen here, etc.
  //std::cout << "test is running" << std::endl;  
  
	//fractal_ptr->SetBounds(glm::vec2(0.0, 0.0), 1.0);
 fractal_ptr->Display();

		//up button
		if (gui_ptr->Button(40, 40, 200, 200, gui_ptr->plus)) 
		{
			fractal_ptr->SetBounds(glm::vec2(0.0, 0.1), 0);
		}

  //renderer_ptr->TestDraw();

   return EM_TRUE;
}


