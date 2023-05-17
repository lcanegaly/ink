#include "object.h"
#include "log.h"

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate): 
  updateDelegate_ptr_{update_delegate}, renderDelegate_ptr_{render_delegate} 
{
  audio_ = nullptr;
}

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate,
         AudioDelegate* audio_delegate) : updateDelegate_ptr_{update_delegate}, 
  renderDelegate_ptr_{render_delegate}, audio_{audio_delegate}{

} 

glm::vec2 Object::position(){
  return glm::vec2(object_.positionX, object_.positionY);
}

glm::vec2 Object::size(){
  return glm::vec2(object_.sizeX, object_.sizeY);
}

float Object::rotation() {
  return object_.rotation;
}

void Object::PlaySound(){
  if (!audio_){
    LOG("ERROR - NO AUDIO DELEGATE\n");
    return; 
  }
  audio_->PlaySound();
} 

void Object::LoadSound(const char* filename){
  audio_->LoadSound(filename); 
} 

void Object::Load(const char * filepath){
  renderDelegate_ptr_->Load(filepath);
}
std::string Object::name() {
  return object_.name;
}
void Object::Update() {
  updateDelegate_ptr_->Update();
}

void Object::set_name(std::string name) {
  object_.name = name;
}

void Object::Draw() {
  renderDelegate_ptr_->Draw();
}

void Object::set_position(glm::vec2 position, float rotation){
  object_.positionX = position.x;
  object_.positionY = position.y;
  object_.rotation = rotation;
}

void Object::set_size(glm::vec2 size){
  object_.sizeX = size.x;
  object_.sizeY = size.y;
}

void Object::set_updateDelegate(UpdateDelegate* updateDelegate){
  updateDelegate_ptr_ = updateDelegate;
}

RenderDelegate* Object::render_delegate() {
  return renderDelegate_ptr_;
}

UpdateDelegate* Object::update_delegate() {
  return updateDelegate_ptr_;
}

AudioDelegate* Object::audio(){
  return audio_;
}
