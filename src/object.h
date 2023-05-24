#pragma once
#include "glm.hpp"
#include <string>
#include <chrono>
#include <vector>
#include <functional>

class ObjectInterface;
class Renderer;

class UpdateDelegate {
 public:
  virtual void Update(std::time_t delta_t) =0; //{}
  //virtual void Update(int position_x, int position_y) = 0; // {}
  //virtual void Update(int position_x, int position_y, float rotation_r) = 0; // {}
  virtual ObjectInterface* context() = 0;// {return object_ptr_;}
 protected:
  ~UpdateDelegate(){}
};

class NoUpdate : public UpdateDelegate{
  virtual void Update(std::time_t delta_t) {}
  //virtual void Update(int position_x, int position_y) {}
  //virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return nullptr;}
 protected:
  ~NoUpdate(){}
}; 

class ScriptUpdate : public UpdateDelegate{
 public:
  ScriptUpdate(std::function<void()> func):onUpdate_{func}
  {}
  virtual void Update(std::time_t delta_t) {
    if (onUpdate_ != nullptr)
      onUpdate_();
  }
  //virtual void Update(int position_x, int position_y) {}
  //virtual void Update(int position_x, int position_y, float rotation_r) {}
  virtual ObjectInterface* context() {return nullptr;}
 private:
  std::function<void()> onUpdate_;
}; 

//TODO - constructor..
class ButtonUpdate : public UpdateDelegate {
  virtual void Update(std::time_t delta_t) {}
  //virtual void Update(int position_x, int position_y) {}
  //virtual void Update(int position_x, int position_y, float rotation_r) {}
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

class Invisible : public RenderDelegate {
 public:
  virtual void Draw() {}
  virtual ObjectInterface* context() { return nullptr;}
  virtual Renderer* renderer() {return nullptr;}  
  virtual void Load() {}
  virtual void Load(const char* filepath) {}
};

class AudioDelegate {
 public:
  virtual void PlaySound() = 0;
  virtual void LoadSound(const char*) = 0;
 protected:
  ~AudioDelegate(){}
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

class ObjectInterface : public AudioDelegate {
 public:
  virtual ~ObjectInterface() {}
  virtual glm::vec2 position() = 0;
  virtual glm::vec2 size() = 0;
  virtual float rotation() = 0;
  virtual std::string name() = 0;
  virtual void Update(std::time_t delta_t) = 0;
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
  Object(UpdateDelegate* update_delegate, RenderDelegate* render_delegate,
         AudioDelegate* audio_delegate);
 
 public:
  virtual void Update(std::time_t delta_t) override;
  virtual void OnUserUpdate(std::time_t delta_t) {}
  virtual void Draw() override;
  virtual void PlaySound();
  virtual void LoadSound(const char*);
  virtual void Load(const char*) override;
  virtual void PushNode(Object* obj); 
  virtual Object& Node( std::string name);

 public:
  virtual glm::vec2 position() override;
  virtual glm::vec2 size() override;
  virtual float rotation() override;
  virtual std::string name() override;
 
 public: 
  virtual void set_name(std::string name) override;
  virtual void set_position(glm::vec2 position, float rotation) override;
  virtual void set_size(glm::vec2 size) override;
  void set_updateDelegate(UpdateDelegate* updateDelegate);

 protected:
  time_t elapsed_time_;
  RenderDelegate* render_delegate() override;
  UpdateDelegate* update_delegate() override;
  AudioDelegate* audio();
  void set_root(Object* root) {root_ = root;}
  Object* root() { return root_; }

 private:
  ObjectData object_;
  UpdateDelegate* updateDelegate_ptr_;
  RenderDelegate* renderDelegate_ptr_;
  AudioDelegate* audio_;
  Object* root_;
  std::vector<Object*> nodes_;
};



