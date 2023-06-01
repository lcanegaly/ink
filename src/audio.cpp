#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"
#include <stdio.h>
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
    (void)pInput;
}

AudioManager::AudioManager(){
  device_config_ = ma_device_config_init(ma_device_type_playback);
  device_config_.playback.format   = decoder_.outputFormat;
  device_config_.playback.channels = decoder_.outputChannels;
  device_config_.sampleRate        = decoder_.outputSampleRate;
  device_config_.dataCallback      = data_callback;
  device_config_.pUserData         = &decoder_;

  if (ma_device_init(NULL, &device_config_, &device_) != MA_SUCCESS) {
    printf("Failed to open playback device.\n");
    ma_decoder_uninit(&decoder_);
    return;
  }
}

int AudioManager::Play(){
  if (ma_device_start(&device_) != MA_SUCCESS) {
    printf("Failed to start playback device.\n");
    ma_device_uninit(&device_);
    ma_decoder_uninit(&decoder_);
    return 0;
  }
  return 1;
}

int AudioManager::Load(const char* file){
  result_ = ma_decoder_init_file(file, NULL, &decoder_);
  if (result_ != MA_SUCCESS) {
    printf("Could not load audio file\n");
    return 0;
  }
  return 1;
}

//for destructor TODO    
    //ma_device_uninit(&device);
    //ma_decoder_uninit(&decoder);


SoundEffect::SoundEffect(const char* filename){
  AudioManager::Get().Load(filename);
}

void SoundEffect::PlaySound(){
  AudioManager::Get().Play();
}

void SoundEffect::LoadSound(const char* filename){
  AudioManager::Get().Load(filename);
} 

