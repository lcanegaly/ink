#include "image_view.h"
#include "vec2.h"
#include "image.h"

ImageView::ImageView(Vec2 size, Vec2 pos): Object(new NoUpdate(), new DrawTexture(this))  { 

}

void ImageView::Draw(){
  image_.Draw(250, 250, 0 , 0);
} 

void ImageView::Point(int size, Vec2 pos){
  return;
}
