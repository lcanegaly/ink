#include "Texture.h"
#include <iostream>

Texture::Texture()
	: m_TexSize{0}, m_Pixel{nullptr}, m_PixelPosition{0}, m_TextureSize{0}, m_Rotation{0}
{
}

Texture::~Texture(){
 delete m_TargaPtr; 
}

void Texture::CreateTexture(const char* filepath)
{
  m_TargaPtr = new Targa(filepath);
}

unsigned char* Texture::GetTexture() const
{
	return (unsigned char*)m_TargaPtr->data();
}

glm::vec2 Texture::GetSize()const 
{
	return glm::vec2(m_TargaPtr->width(), m_TargaPtr->height());
}


