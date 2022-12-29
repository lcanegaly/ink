#pragma once
#include "glm.hpp"
#include <string>

class ObjectInterface;
class Renderer;

class UpdateDelegate {
 public:
  //UpdateDelegate(ObjectInterface* obj): object_ptr_{obj}{}
  virtual void Update() =0; //{}
  virtual void Update(int position_x, int position_y) = 0; // {}
  virtual void Update(int position_x, int position_y, float rotation_r) = 0; // {}
  virtual ObjectInterface* context() = 0;// {return object_ptr_;}
 //private:
  //ObjectInterface* object_ptr_;
};

class NoUpdate : public UpdateDelegate{

  virtual void Update() {}
  virtual void Update(int position_x, int position_y) {}
  virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return nullptr;}
 protected:
  ~NoUpdate(){}
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
  //RenderDelegate (ObjectInterface* object, Renderer* renderer): 
  //  object_ptr_{object}, renderer_ptr_{renderer}
  //{}
  //~RenderDelegate(){
  //}
  virtual void Draw() = 0;// {}
  virtual ObjectInterface* context() = 0; //{return object_ptr_;}
  virtual Renderer* renderer() = 0; // {return renderer_ptr_;}  
  virtual void Load() = 0;// {}
  virtual void Load(const char* filepath) = 0;// {}
// private:
  //ObjectInterface* object_ptr_;
  //Renderer* renderer_ptr_;
};


struct ObjectData {
  ObjectData():name{0}, positionX{0}, positionY{0}, 
    sizeX{0}, sizeY{0}, rotation{0}
  {}
  std::string name;
  int positionX, positionY;
  int sizeX, sizeY;
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
  virtual void set_position(glm::vec2 position) = 0;
  virtual void set_size(glm::vec2 size) = 0;
protected:
  virtual RenderDelegate* render_delegate() = 0;
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
  virtual void set_position(glm::vec2 position) override;
  virtual void set_size(glm::vec2 size) override;
  int test;
 protected:
  RenderDelegate* render_delegate() override;
  
 private:
  ObjectData object_;
  RenderDelegate* renderDelegate_ptr_;
  UpdateDelegate* updateDelegate_ptr_;
};



