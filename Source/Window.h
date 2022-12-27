#pragma once
#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
//#include "MouseInput.h"

class WindowDelegate {
 public:
  virtual int Create(int width, int height, const char* title) = 0; 
  virtual void Destroy() = 0;
  virtual GLFWwindow* context() = 0;
};

class GLFWContext : public WindowDelegate {
 public:
  GLFWContext(int width, int height, const char* title);  
 //	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
 //	void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
  GLFWwindow* context() override;
	int Create(int width, int height, const char* title) override; 
  void Destroy() override;
  GLFWwindow* window_;
};
/*
  void Swap()
  { 
  glfwSwapBuffers(window);
  if (!window){
    std::cout << "window ptr empty" << std::endl;
  }
  }

void Clear(float r = 0.0f, float g = 0.0f, float b = 1.0f, float a = 1.0f)
	{
		glClearColor(0.55f, 0.3f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
   //     	glfwSwapBuffers(window); // stub
   //     	glfwSwapInterval(0); // stub
	}

*/
 
/*
	void GetMouseInput(MouseInput& outMouse)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
  
    std::cout << mouse.m_MouseY << " : " << mouse.m_MouseX << " \n";
		
  outMouse = mouse;
		mouse.Clear();
	}
	
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			mouse.m_LeftClick = true;
			mouse.m_RightClick = false;
			mouse.m_MouseX = xpos;
			mouse.m_MouseY = ypos;
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
			mouse.m_LeftClick = false;
			mouse.m_RightClick = true;
			mouse.m_MouseX = xpos;
			mouse.m_MouseY = ypos;
		}
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(-0.1, 0.0), 0);//left

		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(0.1, 0.0), 0); //right

		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(0.0, 0.1), 0); //up

		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(0.0, -0.1), 0); //down

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(0.0, 0.0), -0.1);//Zoom out

		if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
			fractal_ptr->SetBounds(glm::vec2(0.0, 0.0), 0.1);//Zoom in
	}

	int ShouldClose() 
	{
		return glfwWindowShouldClose(window);
	}

*/

