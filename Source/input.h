#pragma once
#include "glm.hpp"
#include <emscripten.h>
#include <emscripten/html5.h>
#include "log.h"
#include <string>
#include <vector>


class KeyCallback {
 public:
  virtual void Call(std::string keys){}
};

template<typename T>
class KeyCallback_T : public KeyCallback {
 public:
  KeyCallback_T(T* object, void(T::* f)(std::string))
    :object_{object}, func_ptr_{f}
  {}
  void Call(std::string keys) override {
    (object_->*func_ptr_)(keys);
  }
 private:
  T* object_;
  void (T::* func_ptr_)(std::string);
};

struct InputData{
	double MouseX;
	double MouseY;
	bool LeftClick;
	bool RightClick;
  std::string key;
};

class InputDelegate {
 public:
  virtual glm::vec2 GetMousePosition() = 0;
  virtual bool GetMouseClick() = 0;
  virtual std::string GetKeys() = 0;
  virtual void Reset() = 0;
};

class EmscriptenInput : public InputDelegate {
 public:
  EmscriptenInput(){
    if (!init_){
      init_ = true;
      EMSCRIPTEN_RESULT ret = emscripten_set_click_callback("canvas", 0, 1, &mouse_callback);
      ret = emscripten_set_keypress_callback("canvas", 0, 1, &key_callback);
    }
  }
  static EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData) {
    input_.MouseX = mouseEvent->targetX;
    input_.MouseY = mouseEvent->targetY;
    input_.LeftClick = true;
    return 0;
  }

  template<typename T>
  static void RegisterKeyCallback(T* object, void(T::* func)(std::string keys)){
    callback_.push_back(new KeyCallback_T<T>(object, func));
  }

  static EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData){
    LOG(keyEvent->key);
    std::string key(keyEvent->key);
    input_.key = key;
    for(auto& x : callback_)
      x->Call(key);
    return 0;
  }

  glm::vec2 GetMousePosition() override {return glm::vec2(input_.MouseX, input_.MouseY);}
  bool GetMouseClick() override {return input_.LeftClick;}
  std::string GetKeys() override {return input_.key;}
  void Reset() override {
    input_.MouseY = 0;
    input_.MouseX = 0;
    input_.LeftClick = 0;
  }
private:
  static std::vector<KeyCallback*> callback_;
  static bool init_;
  static InputData input_;
};

