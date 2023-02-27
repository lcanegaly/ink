#pragma once
#include "glm.hpp"
#include <string>
#include <functional>

class ObjectInterface;
class Renderer;

class UpdateDelegate {
 public:
  virtual void Update() =0; //{}
  virtual void Update(int position_x, int position_y) = 0; // {}
  virtual void Update(int position_x, int position_y, float rotation_r) = 0; // {}
  virtual ObjectInterface* context() = 0;// {return object_ptr_;}
 protected:
  ~UpdateDelegate(){}
};

class NoUpdate : public UpdateDelegate{
  virtual void Update() {}
  virtual void Update(int position_x, int position_y) {}
  virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return nullptr;}
 protected:
  ~NoUpdate(){}
}; 

class ScriptUpdate : public UpdateDelegate{
 public:
  ScriptUpdate(std::function<void()> func):onUpdate_{func}
  {}
  virtual void Update() {
    if (onUpdate_ != nullptr)
      onUpdate_();
  }
  virtual void Update(int position_x, int position_y) {}
  virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return nullptr;}
 private:
  std::function<void()> onUpdate_;
}; 

//TODO - constructor..
class ButtonUpdate : public UpdateDelegate {
  virtual void Update() {}
  virtual void Update(int position_x, int position_y) {}
  virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return object_ptr_;}
private:
  ObjectInterface* object_ptr_;
};

class RenderDelegate {
 public:
  virtual void Draw() = 0;// {}
  virtual ObjectInterface* context() = 0; //{return object_ptr_;}
  virtual Renderer* renderer() = 0; // {return renderer_ptr_;}  
  virtual void Load() = 0;// {}
  virtual void Load(const char* filepath) = 0;// {}
};


struct ObjectData {
  ObjectData():name{0}, positionX{0}, positionY{0}, 
    sizeX{0}, sizeY{0}, rotation{0}
  {}
  std::string name;
  int positionX, positionY;
  int sizeX;
  int sizeY;
  float rotation;
};

class ObjectInterface {
 public:
  virtual ~ObjectInterface() {}
  virtual glm::vec2 position() = 0;
  virtual glm::vec2 size() = 0;
  virtual float rotation() = 0;
  virtual std::string name() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
  virtual void Load(const char*) = 0;
  virtual void set_name(std::string name) = 0;
  virtual void set_position(glm::vec2 position, float rotation) = 0;
  virtual void set_size(glm::vec2 size) = 0;
protected:
  virtual RenderDelegate* render_delegate() = 0;
  virtual UpdateDelegate* update_delegate() = 0;
};

class Object : public ObjectInterface {
public:
  Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate);
  virtual glm::vec2 position() override;
  virtual glm::vec2 size() override;
  virtual float rotation() override;
  virtual std::string name() override;
  virtual void Update() override;
  virtual void Draw() override;
  virtual void Load(const char*) override;
  virtual void set_name(std::string name) override;
  virtual void set_position(glm::vec2 position, float rotation) override;
  virtual void set_size(glm::vec2 size) override;
  void set_updateDelegate(UpdateDelegate* updateDelegate);

 protected:
  RenderDelegate* render_delegate() override;
  UpdateDelegate* update_delegate() override;
  
 private:
  ObjectData object_;
  UpdateDelegate* updateDelegate_ptr_;
  RenderDelegate* renderDelegate_ptr_;
};



