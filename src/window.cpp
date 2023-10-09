#include "input.h"
#include "window.h"


GLFWContext::GLFWContext(int width, int height, const char* title) {
  if (!glfwInit())
      return;
  glfwDefaultWindowHints();
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2); //wasm support may need this.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API); //wasm support may need this.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window_ = glfwCreateWindow(width, height, title, NULL, NULL);
  assert(window_ != nullptr);
  if (!window_){
    glfwTerminate();
  }
  GLFWInput::SetWindowPointer(window_); 
  glfwMakeContextCurrent(window_);
  glewInit();
  int w, h;
  glfwGetFramebufferSize(window_, &w, &h);
  glViewport(0, 0, w, h);
}
  
GLFWwindow& GLFWContext::context() {
  if (!window_){printf("window_ ptr not set \n");}
  return *window_;
}

void GLFWContext::Destroy() {
	glfwTerminate();
}
