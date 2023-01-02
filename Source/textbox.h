#pragma once
#include "input.h"
#include "renderer.h"
#include "sprite.h"
#include "object.h"
#include <unordered_map>
#include <string>
#include "glm.hpp"


struct Font {
  const char* filepath;
  int columns;
  int rows;
  std::unordered_map<char, Vec2> characterMap; 
};

class TextBox : public Object {
 public:
  TextBox(const char* filepath, Renderer* renderer, int width, int height, int X, int Y):
    Object(new NoUpdate(), new DrawSprite(this, character_, renderer)),text_{0}, input_{new EmscriptenInput()},
    modeInput_{true}, cursorPosition_{1}
  {
    ((EmscriptenInput*)input_)->RegisterKeyCallback<TextBox>(this, &TextBox::UpdateKeys); 
    set_position(glm::vec2(X,Y), 0);
    set_size(glm::vec2(width,height));
    Load(filepath);
    SetupFont();
    character_.bind_num = 1;
    character_.textureColumns = font_.columns;
    character_.textureRows = font_.rows;
    character_.posX = X;
    character_.posY = Y;
    character_.width = width;
    character_.height = height;
    character_.column = 0;
    character_.row = 7;
    character_.rotation = 0;
  }
  //TODO this should load from file. 
  void SetupFont(){
    font_.filepath = "font1.tga";
    font_.columns = 16;
    font_.rows = 8;
    font_.characterMap['a'] = Vec2{7,0};
    font_.characterMap['b'] = Vec2{7,1};
    font_.characterMap['c'] = Vec2{7,2};
    font_.characterMap['d'] = Vec2{7,3};
    font_.characterMap['e'] = Vec2{7,4};
    font_.characterMap['f'] = Vec2{7,5};
    font_.characterMap['g'] = Vec2{7,6};
    font_.characterMap['h'] = Vec2{7,7};
  }
  void UpdateKeys(std::string keys) {
    if (!keys.empty() && modeInput_){
      char c = keys.at(0);
      SetChar(cursorPosition_++, c);
      printf("Position - %d", cursorPosition_);
    }
  }
  void SetChar(int position, char character){
    character_.posX = character_.width*position;
    character_.row = font_.characterMap[character].x;
    character_.column = font_.characterMap[character].y;
  }
 private:
  //TODO - base class should have input delegate pointer. 
  std::string text_; 
  InputDelegate* input_;
  ImageData character_;
  Font font_;
  bool modeInput_;
  int cursorPosition_;
};
