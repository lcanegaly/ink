#include "Texture.h"
#include <iostream>

Texture::Texture()
	: m_TexSize{0}, m_Pixel{nullptr}, m_PixelPosition{0}, m_TextureSize{0}, m_Rotation{0}
{
}

void Texture::CreateTexture(glm::vec2 size)
{
	m_TextureSize = (int)size.x * (int)size.y;
	m_TextureSize = m_TextureSize * 3;
	m_Pixel = new unsigned char[m_TextureSize];
	m_TexSize = size;
}

unsigned char* Texture::GetTexture() const
{
	return m_Pixel;
}

void Texture::SetPixelColor(glm::vec3 color)
{
	//each m_Pixel is vec3
	//set red value
	m_Pixel[m_PixelPosition] = color.x;
	++m_PixelPosition;
	//set green value
	m_Pixel[m_PixelPosition] = color.y;
	++m_PixelPosition;
	//set blue value
	m_Pixel[m_PixelPosition] = color.z;
	++m_PixelPosition;
}

void Texture::SetPixelColor(glm::vec2 pos, glm::vec3 color)
{
	int position = 3 * (pos.x + pos.y * int(m_TexSize.x));
	m_Pixel[position] = color.x;
	m_Pixel[position + 1] = color.y;
	m_Pixel[position + 2] = color.z;
}

glm::vec3 Texture::GetPixelColor(glm::vec2 pos) const
{
	glm::vec3 color{0.0f, 0.0f, 0.0f};
	int position = 3 * (pos.x + pos.y * int(m_TexSize.x));
	
	int x = m_Pixel[position];
	int y = m_Pixel[position + 1];
	int z =	m_Pixel[position + 2];

	color = glm::vec3(x, y, z);

	return color;
}

void Texture::SetRotation(float rotation)
{
	m_Rotation = rotation;
}

float Texture::GetRotation() const
{
	return m_Rotation;
}

void Texture::DrawLine(int x1, int y1, int x2, int y2){
	
	float slope = 0.0f;

	if (x1!=x2){
		slope = (float(y1-y2))/(float(x1-x2));
	}else{
		int yStartingPoint = (y1 > y2) ? y2 : y1;
		for (int y = 0; y < abs(y1-y2); ++y){
			int x = x1;
			int position = 3*(x+((yStartingPoint+y)*int(this->m_TexSize.x)));
			m_Pixel[position]= 100.0f;
			m_Pixel[position+1]= 100.0f;
			m_Pixel[position+2]= 100.0f;
		}
		return;
	}
	
	if (y2 == y1){
		int xStartingPoint = (x1 > x2) ? x2 : x1;
		for (int x = 0; x < abs(x1 - x2); ++x) {
			int y = y1;
			int position = 3 * (xStartingPoint+x + (y * int(this->m_TexSize.x)));
			m_Pixel[position] = 100.0f;
			m_Pixel[position+1] = 100.0f;
			m_Pixel[position+2] = 100.0f;
		}
		return;
	}
		
	int xStartingPoint = 0, yStartingPoint = 0;

	if (slope > 0) {
		if (x1 > x2)
			xStartingPoint = x2, yStartingPoint = y2;
		else
			xStartingPoint = x1, yStartingPoint = y1;
	}
	else if(slope < 0) {
		if (x1 > x2)
			xStartingPoint = x2, yStartingPoint = y1;
		else
			xStartingPoint = x1, yStartingPoint = y2;
	}

	float b = y1 - (slope * x1);
	
	for (int x = 0; x < abs(x1-x2); ++x){
		int y = slope*(xStartingPoint+x)+b;
		int position = 3*((xStartingPoint+x)+(y*int(this->m_TexSize.x)));
		m_Pixel[position]= 100.0f;
		m_Pixel[position+1]= 100.0f;
		m_Pixel[position+2]= 100.0f;
	}
	
	for (int y = 0; y < abs(y1-y2); ++y){
		int x = ((yStartingPoint+y)-b)/slope;
		int position = 3*(x+((yStartingPoint+y)*int(this->m_TexSize.x)));
		m_Pixel[position]= 100.0f;
		m_Pixel[position+1]= 100.0f;
		m_Pixel[position+2]= 100.0f;
	}
}


void Texture::DrawArrow(int x, int y, int sizeX, int sizeY){

	DrawLine(x - sizeX/2, y-sizeY, x, y);
	DrawLine(x + sizeX/2, y - sizeY, x, y);
	DrawLine(x + sizeX / 2, y - sizeY, x - sizeX / 2, y - sizeY);

	FloodFill(glm::vec2(x, y - y * 0.5), glm::vec3(10, 10, 10), glm::vec3(GetPixelColor(glm::vec2(x, y - y * 0.5))));

}

void Texture::DrawPlus(int posX, int posY, int sizeX, int sizeY)
{
	//top, bottom
	DrawLine(sizeX - (sizeX * 0.25f), sizeY + (sizeY * 0.75f), sizeX + (sizeX * 0.25f), sizeY + (sizeY * 0.75f));
	DrawLine(sizeX - (sizeX * 0.25f), sizeY - (sizeY * 0.75f), sizeX + (sizeX * 0.25f), sizeY - (sizeY * 0.75f));
	//left right
	DrawLine(sizeX - (sizeX * 0.75f), sizeY + (sizeY * 0.25f), sizeX - (sizeX * 0.75f), sizeY - (sizeY * 0.25f));
	DrawLine(sizeX + (sizeX * 0.75f), sizeY + (sizeY * 0.25f), sizeX + (sizeX * 0.75f), sizeY - (sizeY * 0.25f));
	//top to middle
	DrawLine(sizeX - (sizeX * 0.25f), sizeY + (sizeY * 0.75f), sizeX - (sizeX * 0.25f), sizeY + (sizeY * 0.25f));
	DrawLine(sizeX + (sizeX * 0.25f), sizeY + (sizeY * 0.75f), sizeX + (sizeX * 0.25f), sizeY + (sizeY * 0.25f));
	//bottom to middle
	DrawLine(sizeX - (sizeX * 0.25f), sizeY - (sizeY * 0.75f), sizeX - (sizeX * 0.25f), sizeY - (sizeY * 0.25f));
	DrawLine(sizeX + (sizeX * 0.25f), sizeY - (sizeY * 0.75f), sizeX + (sizeX * 0.25f), sizeY - (sizeY * 0.25f));
	//left to middle
	DrawLine(sizeX - (sizeX * 0.75f), sizeY + (sizeY * 0.25f), sizeX - (sizeX * 0.25f), sizeY + (sizeY * 0.25f));
	DrawLine(sizeX - (sizeX * 0.75f), sizeY - (sizeY * 0.25f), sizeX - (sizeX * 0.25f), sizeY - (sizeY * 0.25f));
	//right to middle
	DrawLine(sizeX + (sizeX * 0.75f), sizeY + (sizeY * 0.25f), sizeX + (sizeX * 0.25f), sizeY + (sizeY * 0.25f));
	DrawLine(sizeX + (sizeX * 0.75f), sizeY - (sizeY * 0.25f), sizeX + (sizeX * 0.25f), sizeY - (sizeY * 0.25f));

	FloodFill(glm::vec2(posX, posY), glm::vec3(10, 10, 10), glm::vec3(GetPixelColor(glm::vec2(posX, posY))));
}



void Texture::DrawMinus(int posX, int posY, int sizeX, int sizeY)
{
	DrawLine(sizeX - (sizeX * 0.75f), sizeY + (sizeY * 0.25f), sizeX + (sizeX * 0.75f), sizeY + (sizeY * 0.25f));
	DrawLine(sizeX - (sizeX * 0.75f), sizeY - (sizeY * 0.25f), sizeX + (sizeX * 0.75f), sizeY - (sizeY * 0.25f));
	DrawLine(sizeX - (sizeX * 0.75f), sizeY - (sizeY * 0.25f), sizeX - (sizeX * 0.75f), sizeY + (sizeY * 0.25f));
	DrawLine(sizeX + (sizeX * 0.75f), sizeY - (sizeY * 0.25f), sizeX + (sizeX * 0.75f), sizeY + (sizeY * 0.25f));
	FloodFill(glm::vec2(posX, posY), glm::vec3(10, 10, 10), glm::vec3(GetPixelColor(glm::vec2(posX, posY))));
}

//needs some rethinking..
void Texture::FloodFill(glm::vec2 pos, glm::vec3 color, glm::vec3 match)
{
	//fill lines below starting m_Pixel
	int posY = pos.y;
	glm::vec3 pcolor = GetPixelColor(glm::vec2(pos.x, posY));
	while (pcolor == match) {

		
		int posX = pos.x - 1;
		glm::vec3 xcolor = GetPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX > 0) {
				SetPixelColor(glm::vec2(posX, posY), color);
				posX -= 1;
				xcolor = GetPixelColor(glm::vec2(posX, posY));
			}
		}
		
		posX = pos.x + 1;
		xcolor = GetPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < m_TexSize.x) {
				SetPixelColor(glm::vec2(posX, posY), color);
				posX += 1;
				xcolor = GetPixelColor(glm::vec2(posX, posY));
			}
		}

		if (posY > 0) {
			SetPixelColor(glm::vec2(pos.x, posY), color);
			posY -= 1;
			pcolor = GetPixelColor(glm::vec2(pos.x, posY));
		}

	}
	
	//fill lines above starting m_Pixel
	posY = pos.y;
	pcolor = GetPixelColor(glm::vec2(pos.x, posY + 1 ));
	while (pcolor == match) {
		int posX = pos.x + 1;
		glm::vec3 xcolor = GetPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < m_TexSize.x) {
				SetPixelColor(glm::vec2(posX, posY), color);
				posX += 1;
				xcolor = GetPixelColor(glm::vec2(posX, posY));
			}
		}
		posX = pos.x - 1;
		xcolor = GetPixelColor(glm::vec2(posX, posY));
		while (xcolor == match) {
			if (posX < m_TexSize.x) {
				SetPixelColor(glm::vec2(posX, posY), color);
				posX -= 1;
				xcolor = GetPixelColor(glm::vec2(posX, posY));
			}
		}
		if (posY < m_TexSize.y) {
			SetPixelColor(glm::vec2(pos.x, posY), color);
			posY += 1;
			pcolor = GetPixelColor(glm::vec2(pos.x, posY));
		}
	}
}

void Texture::ClearTexture()
{
	delete[] m_Pixel;
	m_Pixel = new unsigned char[m_TextureSize];
	m_PixelPosition = 0;
}

glm::vec2 Texture::GetSize()const 
{
	return m_TexSize;
}