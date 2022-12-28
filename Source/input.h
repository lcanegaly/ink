#pragma once
#include "glm.hpp"
#include <emscripten.h>
#include <emscripten/html5.h>
#include "log.h"

struct InputData{
	double MouseX;
	double MouseY;
	bool LeftClick;
	bool RightClick;
};

class InputDelegate {
 public:
  virtual glm::vec2 GetMousePosition() = 0;
  virtual bool GetMouseClick() = 0;
  virtual void Reset() = 0;
};

class EmscriptenInput : public InputDelegate {
 public:
  static EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
    LOG("Input Event");  
    input_.MouseX = e->targetX;
    input_.MouseY = e->targetY;
    input_.LeftClick = true;
    return 0;
  }
  
  glm::vec2 GetMousePosition() override {return glm::vec2(input_.MouseX, input_.MouseY);}
  bool GetMouseClick() override {return input_.LeftClick;}
  void Reset() override {
    input_.MouseY = 0;
    input_.MouseX = 0;
    input_.LeftClick = 0;
  }
 private:
  static InputData input_;
};

