#include "window.h"

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
  
    /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  int w, h;
  glfwGetFramebufferSize(window_, &w, &h);

  glViewport(0, 0, w, h);
}
	//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	//void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
  
GLFWwindow* GLFWContext::context() {
  if (!window_){printf("window_ ptr not set \n");}
  return window_;
}

int GLFWContext::Create(int width, int height, const char* title) {
  if (!glfwInit())
    return 1;
  // OpenGL ES 2.0
  glfwDefaultWindowHints();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window_ = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!window_){
    glfwTerminate();
    return 1;
  }
  /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  int w, h;
  glfwGetFramebufferSize(window_, &w, &h);

  glViewport(0, 0, w, h);
  return 1;
}

void GLFWContext::Destroy() {
	glfwTerminate();
}
