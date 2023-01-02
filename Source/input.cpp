#include "input.h"


std::vector<KeyCallbackDelegate*> EmscriptenInput::callback_;
bool EmscriptenInput::init_ = false;
InputData EmscriptenInput::input_ {0.0, 0.0, 0,0};

EM_BOOL EmscriptenInput::key_callback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData){
    LOG(keyEvent->key);
    std::string key(keyEvent->key);
    input_.key = key;
    for(auto& x : callback_)
      x->Call(key);
    return 0;
}

EmscriptenInput::EmscriptenInput(){
    if (!init_){
      init_ = true;
      EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("canvas", 0, 1, &mouse_callback);
      //ret = emscripten_set_keypress_callback("canvas", 0, 1, &key_callback);
      ret = emscripten_set_keydown_callback("canvas", 0, 1, &key_callback);
    }
}

EM_BOOL EmscriptenInput::mouse_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
    input_.MouseX = mouseEvent->targetX;
    input_.MouseY = mouseEvent->targetY;
    input_.LeftClick = true;
    return 0;
}

glm::vec2 EmscriptenInput::GetMousePosition() {return glm::vec2(input_.MouseX, input_.MouseY);}
  
bool EmscriptenInput::GetMouseClick() {return input_.LeftClick;}

std::string EmscriptenInput::GetKeys() {return input_.key;}

