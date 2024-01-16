#pragma once
#include <filesystem>
#include <iterator>
#include <unordered_map>

#include "targa/targa.h"
#include "shader.h"
#include "objimp/obj.h"
#include "texture.h"

class AssetManager {
  public:
    Shader& GetShader(const char* name) {
      for (auto& shader : shaders_){
        if (shader.first == name)
          return shader.second;
      }
      std::cout << "could not find shader " << name << "\n";
      return shaders_[0]; //TODO fixme. 
    }
    Texture& GetTexture(std::string name) {
      for (auto& texture : textures_){
        if (texture.first == name)
          return texture.second;
      }
      std::cout << "could not find texture " << name << "\n";
      return textures_[0]; //TODO fixme. 
    }
    objimp::Model& GetModel(std::string name) {
      for (auto& model: models_){
        if (model.first == name)
          return model.second;
      }
      std::cout << "could not find model " << name << "\n";
      return models_[0]; //TODO fixme. 
    }

    // Finds any texture files in dir and loads them
    void FindAndLoadAssets(const char* directory_to_search){
      namespace fs = std::filesystem; 
      try{
        if (fs::exists(directory_to_search) 
          && fs::is_directory(directory_to_search)){
          for (const auto& file : fs::directory_iterator(directory_to_search)){
            std::string name = file.path();
            name = name.substr(2); //strip './'
            // Load obj 
            if (name.find(".tga") != std::string::npos){
              LoadTexture(name, name.substr(0, name.length()-4));
            } 
            else if (name.find(".obj") != std::string::npos){
              LoadObject(name, name.substr(0, name.length()-4));
            } 
        } 
      }
      } catch (fs::filesystem_error& e) {
          std::cerr << "error loading textures: " << e.what() << ": \n";
      }
    }
   
    void LoadTexture(std::string filename, std::string name){
      auto texture = new Targa::TgaImage(filename.c_str());
      auto texture_id = Renderer::Get().LoadTexture((unsigned char*)texture->data(), texture->width(), texture->height(), 4); 
      textures_[name] = Texture{texture_id, texture}; 
      std::cout << textures_.size() << "\n";
    }
    
    void LoadObject(std::string file, std::string name){
      models_[name] = objimp::Model(file.c_str());
      std::cout << models_.size() << "\n";
    }

    void Print(){
      std::cout << "currently loaded textures:\n";
      for (auto t : textures_)
        std::cout << t.first << " ";
      std::cout << "\n";

      std::cout << "currently loaded models:\n";
      for (auto m : models_)
        std::cout << m.first << " ";
      std::cout << "\n";
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
    std::unordered_map<std::string, Texture> textures_;
    std::unordered_map<std::string, objimp::Model> models_;

    AssetManager(){
      // TODO should load this from a file.
      /*  
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
      */

      // ------------ SHADERS ------------
      auto shader = Shader("tex_vertex.sh",
      "tex_fragment.sh");
      //shader.setInt("tex", 0);
      shaders_["texture"] = shader; 
      
      shader = Shader("vertex.sh",
      "fragment.sh");
      shaders_["color"] = shader; 
      /* 
      // ------------ Models ------------
      models_["floor"] = objimp::Model("floor.obj");
      models_["line"] = objimp::Model("line.obj");
      models_["gate"] = objimp::Model("gate.obj");
      models_["doge"] = objimp::Model("doge.obj");
      */ 
    }
};
