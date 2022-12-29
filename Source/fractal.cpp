#include "fractal.h"
#include <iostream>


Fractal::Fractal(glm::vec2 screenSize, glm::vec2 centerPoint, Renderer* renderer) 
	: Object(nullptr, nullptr), 
          m_Calculated{false}, m_ScreenSize{ screenSize }, m_CenterPoint{ centerPoint }, m_Renderer{ renderer }
{
	m_Zoom = 2.0;
}


void Fractal::SetBounds(glm::vec2 centerPoint, double zoom)
{
	m_Calculated = false;
	m_CenterPoint += centerPoint * glm::vec2(m_Zoom, m_Zoom);
	if (zoom > 0)
	{
		m_Zoom /= 1.1;
	}
	if (zoom < 0)
	{
		m_Zoom *= 1.1;
	}
}


void Fractal::Display() const
{
	m_Renderer->DrawFractal(m_ScreenSize.x, m_ScreenSize.y, m_CenterPoint, m_Zoom);
}

void Fractal::Draw() {
	m_Renderer->DrawFractal(m_ScreenSize.x, m_ScreenSize.y, m_CenterPoint, m_Zoom);
}

void Fractal::Update() {
  // no op
}
