#include "label.h"
#include "object.h"
#include <iostream>

Label::Label(const char* filepath, int size, int X, int Y):
    Object(new NoUpdate(), new DrawText(this, character_, font_)),text_{0},
    ticks_per_update_{1}, tick_{0}
  {
    set_position(glm::vec2(X,Y), 0);
    set_size(glm::vec2(size,size));
    Load(filepath);
    //font_.filepath = filepath; 
    SetupFont();
    character_.bind_num = 1;
    character_.texture_columns = font_.columns;
    character_.texture_rows = font_.rows;
    character_.pos_x = X;
    character_.pos_y = Y;
    character_.width = size;
    character_.height = size;
    character_.column = 0;
    character_.row = 7;
    character_.rotation = 0;
}

void Label::SetupFont(){
    font_.filepath = "../client/assets/font1_t.tga";
    font_.columns = 16;
    font_.rows = 8;
    font_.characterMap['a'] = IVec2{7,0};
    font_.characterMap['b'] = IVec2{7,1};
    font_.characterMap['c'] = IVec2{7,2};
    font_.characterMap['d'] = IVec2{7,3};
    font_.characterMap['e'] = IVec2{7,4};
    font_.characterMap['f'] = IVec2{7,5};
    font_.characterMap['g'] = IVec2{7,6};
    font_.characterMap['h'] = IVec2{7,7};
    font_.characterMap['i'] = IVec2{7,8};
    font_.characterMap['j'] = IVec2{7,9};
    font_.characterMap['k'] = IVec2{6,0};
    font_.characterMap['l'] = IVec2{6,1};
    font_.characterMap['m'] = IVec2{6,2};
    font_.characterMap['n'] = IVec2{6,3};
    font_.characterMap['o'] = IVec2{6,4};
    font_.characterMap['p'] = IVec2{6,5};
    font_.characterMap['q'] = IVec2{6,6};
    font_.characterMap['r'] = IVec2{6,7};
    font_.characterMap['s'] = IVec2{6,8};
    font_.characterMap['t'] = IVec2{6,9};
    font_.characterMap['u'] = IVec2{5,0};
    font_.characterMap['v'] = IVec2{5,1};
    font_.characterMap['w'] = IVec2{5,2};
    font_.characterMap['x'] = IVec2{5,3};
    font_.characterMap['y'] = IVec2{5,4};
    font_.characterMap['z'] = IVec2{5,5};
    font_.characterMap['0'] = IVec2{5,6};
    font_.characterMap['1'] = IVec2{5,7};
    font_.characterMap['2'] = IVec2{5,8};
    font_.characterMap['3'] = IVec2{5,9};
    font_.characterMap['4'] = IVec2{4,0};
    font_.characterMap['5'] = IVec2{4,1};
    font_.characterMap['6'] = IVec2{4,2};
    font_.characterMap['7'] = IVec2{4,3};
    font_.characterMap['8'] = IVec2{4,4};
    font_.characterMap['9'] = IVec2{4,5};
    font_.characterMap[' '] = IVec2{4,6};
    font_.characterMap[','] = IVec2{4,7};
    font_.characterMap['.'] = IVec2{4,8};
    font_.characterMap[':'] = IVec2{4,9};
    font_.characterMap['!'] = IVec2{3,0};
    font_.characterMap['-'] = IVec2{3,1};
    font_.characterMap['"'] = IVec2{3,2};
    font_.characterMap['('] = IVec2{3,3};
    font_.characterMap[')'] = IVec2{3,4};
    font_.characterMap['\''] = IVec2{3,5};
    font_.characterMap['?'] = IVec2{3,6};
    font_.characterMap['/'] = IVec2{3,7};
}

void Label::Update(std::time_t delta_t) {
  character_.pos_x = position().x;
  character_.pos_y = position().y;
  character_.width = size().x;
  character_.height = size().y;
  //TODO - dynamic cast this.
  
  //if(update_delegate() && tick_ < 1){
  //  update_delegate()->Update(delta_t);
  //  tick_ = ticks_per_update_;
  //}
  //tick_--;
}

void Label::SetText(const std::string& text) {
  text_ = text;
}
