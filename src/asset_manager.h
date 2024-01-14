#pragma once
#include "targa/targa.h"
#include "shader.h"
#include <unordered_map>
#include "objimp/obj.h"
#include "texture.h"

class AssetManager {
  public:
    Shader& GetShader(const char* name) {
      for (auto& shader : shaders_){
        if (shader.first == name)
          return shader.second;
      }
      return shaders_[0]; //TODO fixme. 
    }
    Texture& GetTexture(const char* name) {
      for (auto& texture : textures_){
        if (texture.first == name)
          return texture.second;
      }
      return textures_[0]; //TODO fixme. 
    }
    objimp::Model& GetModel(const char* name) {
      for (auto& model: models_){
        if (model.first == name)
          return model.second;
      }
      return models_[0]; //TODO fixme. 
    }

  public:
    static AssetManager& Get() {
      static AssetManager instance; 
      return instance;
    }
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
  private:
    std::unordered_map<const char*, Shader> shaders_;
    std::unordered_map<const char*, Texture> textures_;
    std::unordered_map<const char*, objimp::Model> models_;

    AssetManager(){
      // TODO should load this from a file.
      
      // ------------ TEXTURES ------------
      auto texture = new Targa::TgaImage("gate.tga");
      auto texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_["gate"] = Texture{texture_id, texture}; 

      texture = new Targa::TgaImage("test2.tga");
      texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_["test2"] = Texture{texture_id, texture}; 
      
      texture = new Targa::TgaImage("brick.tga");
      texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_["brick"] = Texture{texture_id, texture}; 
      
      texture = new Targa::TgaImage("concrete.tga");
      texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_["concrete"] = Texture{texture_id, texture}; 
 
      texture = new Targa::TgaImage("concrete_tiles.tga");
      texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_["concrete_tile"] = Texture{texture_id, texture}; 


      // ------------ SHADERS ------------
      auto shader = Shader("tex_vertex.sh",
      "tex_fragment.sh");
      shader.setInt("tex", 0);
      shaders_["texture"] = shader; 
      
      shader = Shader("vertex.sh",
      "fragment.sh");
      shaders_["color"] = shader; 
      
      // ------------ Models ------------
      models_["floor"] = objimp::Model("floor.obj");
      models_["line"] = objimp::Model("line.obj");
      models_["gate"] = objimp::Model("gate.obj");
      models_["doge"] = objimp::Model("doge.obj");
    }
};
