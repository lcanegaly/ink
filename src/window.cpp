#include <iostream>
#include "window.h"

GLFWwindow* window_handle = nullptr;

//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
//}
//void key_callback(GLFWwindow*, int key, int scancode, int action, int mods){
//}

GLFWContext::GLFWContext(int width, int height, const char* title) {
  if (!glfwInit())
      return;
  // OpenGL ES 2.0
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window_ = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window_){
    glfwTerminate();
  }
  window_handle = window_; 
  glfwMakeContextCurrent(window_);
  glewInit();
  int w, h;
  glfwGetFramebufferSize(window_, &w, &h);
  //glfwSetKeyCallback(window_, key_callback);
  glViewport(0, 0, w, h);
}
  
GLFWwindow* GLFWContext::context() {
  if (!window_){printf("window_ ptr not set \n");}
  return window_;
}

void GLFWContext::Destroy() {
	glfwTerminate();
}
