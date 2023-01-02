#include "input.h"


std::vector<KeyCallback*> EmscriptenInput::callback_;
bool EmscriptenInput::init_ = false;
InputData EmscriptenInput::input_ {0.0, 0.0, 0,0};
