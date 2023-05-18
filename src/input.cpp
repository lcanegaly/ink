#include "input.h"
#include <algorithm>
#include "window.h"

extern GLFWwindow* window_handle;

std::vector<KeyCallbackDelegate*> GLFWInput::callback_;
bool GLFWInput::init_ = false;
InputData GLFWInput::input_ {0.0, 0.0, 0,0};

glm::vec2 GLFWInput::GetMousePosition(){
  double xpos, ypos;
  glfwGetCursorPos(window_handle, &xpos, &ypos); 
  return glm::vec2{xpos, ypos};
} 

bool GLFWInput::GetMouseClick() {
  if(glfwGetMouseButton(window_handle, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)  
    return true;
  return false;
}

std::string GLFWInput::GetKeys(){
  return std::string{};
}

bool GLFWInput::GetKey(int key_code){
  int state = glfwGetKey(window_handle, key_code);
  if (state == GLFW_PRESS){
    return true;
  }
  return false;
} 

void GLFWInput::Reset() {
    input_.MouseY = 0;
    input_.MouseX = 0;
    input_.LeftClick = 0;
}

std::vector<KeyCallbackDelegate*> EmscriptenInput::callback_;
bool EmscriptenInput::init_ = false;
InputData EmscriptenInput::input_ {0.0, 0.0, 0,0};

/*
EM_BOOL EmscriptenInput::key_callback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData){
  LOG(keyEvent->key);
  std::string key(keyEvent->key);
  input_.key = key;
  std::for_each(std::begin(callback_), std::end(callback_), [&](auto callback){
                  callback->Call(key);
                });
  return 0;
}
*/
EmscriptenInput::EmscriptenInput(){
  if (!init_){
    init_ = true;
    //EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("canvas", 0, 1, &mouse_callback);
    //ret = emscripten_set_keydown_callback("canvas", 0, 1, &key_callback);
  }
}
/*
EM_BOOL EmscriptenInput::mouse_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
  input_.MouseX = mouseEvent->targetX;
  input_.MouseY = mouseEvent->targetY;
  input_.LeftClick = true;
  return 0;
}
*/
glm::vec2 EmscriptenInput::GetMousePosition() {return glm::vec2(input_.MouseX, input_.MouseY);}
  
bool EmscriptenInput::GetMouseClick() {return input_.LeftClick;}

std::string EmscriptenInput::GetKeys() {return input_.key;}

