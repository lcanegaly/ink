#pragma once
#include <vector>
#include "../Source/application.h"

class Demo: public Application {
 public:
  Demo(const char* name, int width, int height); 
  void OnUserUpdate() override;
  void LoadDemo(); 
 private:
};

