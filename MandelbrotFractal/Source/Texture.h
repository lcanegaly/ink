#pragma once
#define GLEW_STATIC
#include "glm.hpp"
#include <vector>
#include <utility>
#include "targa.h"

class Texture 
{
public:
	Texture();
  ~Texture();
	void CreateTexture(const char* filepath);
	unsigned char* GetTexture() const;
	void ClearTexture();
	glm::vec2 GetSize() const;


  private:
  Targa* m_TargaPtr = nullptr;
  glm::vec2 m_TexSize;
	unsigned char* m_Pixel;
	int m_PixelPosition;
	long m_TextureSize;
	float m_Rotation;
};
