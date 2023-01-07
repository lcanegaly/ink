#include "label.h"


Label::Label(const char* filepath, Renderer* renderer, int width, int height, int X, int Y):
    Object(new NoUpdate(), new DrawText(this, character_, font_, renderer)),text_{0}
  {
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

void Label::SetupFont(){
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
    font_.characterMap['i'] = Vec2{7,8};
    font_.characterMap['j'] = Vec2{7,9};
    font_.characterMap['k'] = Vec2{6,0};
    font_.characterMap['l'] = Vec2{6,1};
    font_.characterMap['m'] = Vec2{6,2};
    font_.characterMap['n'] = Vec2{6,3};
    font_.characterMap['o'] = Vec2{6,4};
    font_.characterMap['p'] = Vec2{6,5};
    font_.characterMap['q'] = Vec2{6,6};
    font_.characterMap['r'] = Vec2{6,7};
    font_.characterMap['s'] = Vec2{6,8};
    font_.characterMap['t'] = Vec2{6,9};
    font_.characterMap['u'] = Vec2{5,0};
    font_.characterMap['v'] = Vec2{5,1};
    font_.characterMap['w'] = Vec2{5,2};
    font_.characterMap['x'] = Vec2{5,3};
    font_.characterMap['y'] = Vec2{5,4};
    font_.characterMap['z'] = Vec2{5,5};
    font_.characterMap['0'] = Vec2{5,6};
    font_.characterMap['1'] = Vec2{5,7};
    font_.characterMap['2'] = Vec2{5,8};
    font_.characterMap['3'] = Vec2{5,9};
    font_.characterMap['4'] = Vec2{4,0};
    font_.characterMap['5'] = Vec2{4,1};
    font_.characterMap['6'] = Vec2{4,2};
    font_.characterMap['7'] = Vec2{4,3};
    font_.characterMap['8'] = Vec2{4,4};
    font_.characterMap['9'] = Vec2{4,5};
    font_.characterMap[' '] = Vec2{4,6};
    font_.characterMap[','] = Vec2{4,7};
    font_.characterMap['.'] = Vec2{4,8};
    font_.characterMap[':'] = Vec2{4,9};
    font_.characterMap['!'] = Vec2{3,0};
    font_.characterMap['-'] = Vec2{3,1};
    font_.characterMap['"'] = Vec2{3,2};
    font_.characterMap['('] = Vec2{3,3};
    font_.characterMap[')'] = Vec2{3,4};
    font_.characterMap['\''] = Vec2{3,5};
    font_.characterMap['?'] = Vec2{3,6};
    font_.characterMap['/'] = Vec2{3,7};
}

void Label::Update() {
  character_.posX = position().x;
  character_.posY = position().y;
  character_.width = size().x;
  character_.height = size().y;

  //TODO - dynamic cast this.
  ((DrawText*)render_delegate())->DrawString(text_);
}

void Label::SetText(const std::string text) {
  text_ = text;
}
