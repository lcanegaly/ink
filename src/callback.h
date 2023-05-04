#pragma once
#include <vector>
#include <string>

class Callback_T {
 public:
  virtual void Call() = 0;
};

template<typename T, typename P>
class Callback : public Callback_T {
 public:
  Callback(T* object, void(T::* f)(P), P payload)
    :object_{object}, func_ptr_{f}, payload_{payload}
  {}
  void Call() override {
    (object_->*func_ptr_)(payload_);
  }
  void SetPayload(P payload){
    payload_ = payload;
  }
 private:
  T* object_;
  P payload_;
  void (T::* func_ptr_)(P);
};

class Notifier : public Callback_T {
 public:
  Notifier(){}
  ~Notifier(){}
  void Add(Callback_T* callback){
    callbacks_.push_back(callback);
  }
  void Call() {
    for (auto& x : callbacks_)
      x->Call();
  }
 private:
  std::vector<Callback_T*> callbacks_;
};
