#pragma once
#include "object.h"
#include "miniaudio.h"


class AudioManager{
public:
  AudioManager(const AudioManager&) = delete;
  static AudioManager& Get(){
    static AudioManager instance;
    return instance;
  }
  int Play();
  int Load(const char* file);
private:
  AudioManager();

private:
  ma_result result_;
  ma_decoder decoder_;
  ma_device_config device_config_;
  ma_device device_;
};

class SoundEffect : public AudioDelegate {
 public: 
  SoundEffect() = default;
  SoundEffect(const char* filename);

 public:
  void PlaySound() override;
  void LoadSound(const char* filename) override;

 private:

};

class Silent : public AudioDelegate {
 public: 
  Silent() = default;

 public:
  void PlaySound() override {}
  void LoadSound(const char* filename) override {};
};
