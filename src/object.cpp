#include <chrono>
#include <memory>

#include "object.h"
#include "log.h"

Object::Object() : update_delegate_{new NoUpdate}, 
  render_delegate_{new Invisible}, audio_delegate_{nullptr} {}

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate): 
    elapsed_time_{0}, update_delegate_{update_delegate}, 
    render_delegate_{render_delegate}, audio_delegate_{nullptr} {}

Object::Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate,
    AudioDelegate* audio_delegate) : elapsed_time_{0}, 
    update_delegate_{update_delegate}, render_delegate_{render_delegate}, 
    audio_delegate_{audio_delegate} {} 

glm::vec2 Object::position() {
  return glm::vec2(object_.positionX, object_.positionY);
}

glm::vec2 Object::size() {
  return glm::vec2(object_.sizeX, object_.sizeY);
}

float Object::rotation() {
  return object_.rotation;
}

void Object::PlaySound() {
  if (!audio_delegate_){
    LOG("ERROR - NO AUDIO DELEGATE\n");
    return; 
  }
  audio_delegate_->PlaySound();
} 

void Object::LoadSound(const char* filename) {
  audio_delegate_->LoadSound(filename); 
} 

void Object::Load(const char * filepath) {
  render_delegate_->Load(filepath);
}

void Object::PushNode(Object* obj) { 
  nodes_.emplace_back(obj);
  obj->set_root(this);
}

void Object::PushNode(Object* obj, std::string name) {
  PushNode(obj);
  obj->set_name(name);
}

void Object::PopNode( std::string name) {
  int del = -1; 
  for (int i = 0; i < nodes_.size(); i++) {
    if (nodes_[i]->name() == name)
      del = i;
  }  
  if (del > -1){
    nodes_.erase(nodes_.begin() + del);
  }
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
  OnUserUpdate(delta_t); 
  update_delegate_->Update(delta_t);
  for (auto& x : nodes_)
    x->Update(delta_t);
}

void Object::set_name(std::string name) {
  object_.name = name;
}

void Object::Draw() {
  render_delegate_->Draw();
  for (auto& x : nodes_)
    x->Draw();
}

//set_position and update all nodes
void Object::set_position(glm::vec2 position, float rotation) {
  int dX = position.x - object_.positionX; 
  int dY = position.y - object_.positionY; 
  int dA = rotation - object_.rotation; 
  object_.positionX = position.x;
  object_.positionY = position.y; 
  object_.rotation = rotation;
  for (auto& x : nodes_) {
    x->set_position(glm::vec2{x->position().x + dX, 
                              x->position().y + dY}, 
                    x->rotation() + dA); 
  }
}

void Object::set_size(glm::vec2 size) {
  object_.sizeX = size.x;
  object_.sizeY = size.y;
}

void Object::set_updateDelegate(UpdateDelegate* updateDelegate) {
  update_delegate_.reset(updateDelegate);
}

RenderDelegate& Object::render_delegate() {
  return *render_delegate_;
}

UpdateDelegate& Object::update_delegate() {
  return *update_delegate_;
}

AudioDelegate& Object::audio() {
  return *audio_delegate_;
}
