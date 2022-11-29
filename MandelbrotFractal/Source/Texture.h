#pragma once
#define GLEW_STATIC
#include "glm.hpp"
#include <vector>
#include <utility>

class Texture 
{
public:
	Texture();
	void CreateTexture(glm::vec2 size);
	unsigned char* GetTexture() const;
	void ClearTexture();
	glm::vec2 GetSize() const;

	void SetRotation(float rotation);
	float GetRotation() const;

	void SetPixelColor(glm::vec3 color);
	void SetPixelColor(glm::vec2 pos, glm::vec3 color);
	glm::vec3 GetPixelColor(glm::vec2 pos) const;

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawArrow(int x, int y, int sizeX, int sizeY);
	void DrawPlus(int posX, int posY, int sizeX, int sizeY);
	void DrawMinus(int posX, int posY, int sizeX, int sizeY);
	void FloodFill(glm::vec2 pos, glm::vec3 color, glm::vec3 match);
	
private:
	glm::vec2 m_TexSize;
	unsigned char* m_Pixel;
	int m_PixelPosition;
	long m_TextureSize;
	float m_Rotation;
};
