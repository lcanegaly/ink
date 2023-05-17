#pragma once
#include <string>
#include <vector>

#include "glm.hpp"
#include "log.h"
//#include <emscripten.h>
//#include <emscripten/html5.h>

class KeyCallbackDelegate {
 public:
  virtual void Call(std::string keys){}
};

template<typename T>
class KeyCallback : public KeyCallbackDelegate {
 public:
  KeyCallback(T* object, void(T::* f)(std::string))
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
  virtual bool GetKey(int key_code) = 0;
  virtual void Reset() = 0;
};

class GLFWInput : public InputDelegate {
 public: 
  GLFWInput();
  glm::vec2 GetMousePosition() override; 
  bool GetMouseClick() override;
  std::string GetKeys() override;
  virtual bool GetKey(int key_code) override;
  void Reset()override; 
 private:
  static std::vector<KeyCallbackDelegate*> callback_;
  static bool init_;
  static InputData input_;
};

class EmscriptenInput : public InputDelegate {
 public:
  EmscriptenInput();
  //static EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
  //static EM_BOOL key_callback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
  glm::vec2 GetMousePosition() override; 
  bool GetMouseClick() override;
  std::string GetKeys() override;
  bool GetKey(int key_code) override{return false;}
  void Reset() override {
    input_.MouseY = 0;
    input_.MouseX = 0;
    input_.LeftClick = 0;
  }
  template<typename T>
  static void RegisterKeyCallback(T* object, void(T::* func)(std::string keys)){
    callback_.push_back(new KeyCallback<T>(object, func));
  }
private:
  static std::vector<KeyCallbackDelegate*> callback_;
  static bool init_;
  static InputData input_;
};
