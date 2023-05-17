#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

extern GLFWwindow* window_handle;

class WindowDelegate {
 public:
  virtual int Create(int width, int height, const char* title) = 0; 
  virtual void Destroy() = 0;
  virtual GLFWwindow* context() = 0;
  virtual int shouldClose() = 0;
  virtual void PollEvents() = 0;
};

class GLFWContext : public WindowDelegate {
 public:
  GLFWContext(int width, int height, const char* title);  
  GLFWwindow* context() override;
	int Create(int width, int height, const char* title) override{return 1;} 
  void Destroy() override;
  int shouldClose() override {return glfwWindowShouldClose(window_);}
  void PollEvents() override {glfwPollEvents();}
  GLFWwindow* window_;
};

