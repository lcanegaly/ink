#include <chrono>

#include "object.h"
#include "log.h"

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate): 
  elapsed_time_{0}, updateDelegate_ptr_{update_delegate}, renderDelegate_ptr_{render_delegate} 
{
  audio_ = nullptr;
}

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate,
         AudioDelegate* audio_delegate) : elapsed_time_{0}, updateDelegate_ptr_{update_delegate}, 
  renderDelegate_ptr_{render_delegate}, audio_{audio_delegate}, root_{nullptr}{
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

void Object::PushNode(Object* obj) { 
  nodes_.push_back(obj);
  obj->set_root(this);
}

// TODO - rewrite to handle empty node lists and no matches
Object& Object::Node(std::string name) {
  for (auto &x : nodes_)
    if (x->name() == name) return *x;
}

std::string Object::name() {
  return object_.name;
}
void Object::Update(std::time_t delta_t) {
  updateDelegate_ptr_->Update(delta_t);
  for (auto x : nodes_)
    x->Update(delta_t);
}

void Object::set_name(std::string name) {
  object_.name = name;
}

void Object::Draw() {
  renderDelegate_ptr_->Draw();
  for (auto x : nodes_)
    x->Draw();
}

//set_position and update all nodes
void Object::set_position(glm::vec2 position, float rotation){
  int dX = position.x - object_.positionX; 
  int dY = position.y - object_.positionY; 
  int dA = rotation - object_.rotation; 

  object_.positionX = position.x;
  object_.positionY = position.y; 
  object_.rotation = rotation;

  for (auto x : nodes_){
    x->set_position(glm::vec2{x->position().x + dX, 
                              x->position().y + dY}, 
                    x->rotation() + dA); 
  }
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
