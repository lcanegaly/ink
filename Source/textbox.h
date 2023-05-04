#pragma once
#include "input.h"
#include "renderer.h"
#include "sprite.h"
#include "object.h"
#include <unordered_map>
#include <string>
#include "glm.hpp"

//TODO should be a seperate file/class
struct Font {
  const char* filepath;
  int columns;
  int rows;
  std::unordered_map<char, Vec2> characterMap; 
};

class DrawText : public RenderDelegate {
 public:
  DrawText(ObjectInterface* object, ImageData& image_data, Font& font);
  virtual void Draw();
  virtual void DrawString(std::string& text);
  virtual int SetChar(int position, char character);
  virtual ObjectInterface* context();
  virtual Renderer* renderer(); 
  virtual void Load();
  virtual void Load(const char* filepath); 
  Vec2 Lookup(char character);
 private:
  ImageData& data_;
  Font& font_;
  Targa::Image* spriteSheet_;
  ObjectInterface* context_;
  Renderer* renderer_;
  int cursorPosition_;
  int columns_;
  int rows_;
  int column_;
  int row_;
};

class TextBox : public Object {
 public:
  TextBox(const char* filepath, int width, int height, int X, int Y);
  //TODO this should load from file. 
  void SetupFont();
  void UpdateKeys(std::string keys);
  //TODO should be delegate
  void Update()override; 
  void SetText(const std::string text);
 private:
  //TODO - base class should have input delegate pointer. 
  std::string text_; 
  InputDelegate* input_;
  ImageData character_;
  Font font_;
  bool modeInput_;
};
