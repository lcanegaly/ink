#pragma once
#define GLEW_STATIC
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "MouseInput.h"

namespace Window {

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
  static GLFWwindow* window = nullptr;
	MouseInput mouse;

	int Create(int width, int height) 
	{
	
    // OpenGL ES 2.0
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

		return 0;
	}

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

	void Close() 
	{
		glfwTerminate();
	}

	void GetMouseInput(MouseInput& outMouse)
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
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
		/*
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
		*/
	}

	int ShouldClose() 
	{
		return glfwWindowShouldClose(window);
	}

}

