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

