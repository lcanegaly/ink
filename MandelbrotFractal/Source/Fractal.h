#pragma once
#include "glm.hpp"
#include "Renderer.h"
#include "Texture.h"
#include <complex>

class Fractal 
{
public:
	Fractal(glm::vec2 screenSize, glm::vec2 centerPoint, Renderer& renderer);
	//sets the coordinate plane bounds
	void SetBounds(glm::vec2 centerPoint, double zoom);
	void Display() const;

private:
	double m_Zoom;
	const double m_IterationLimit = 500;
	bool m_Calculated;
	glm::vec2 m_ScreenSize;
	glm::vec2 m_CenterPoint;
	Renderer& m_Renderer;

};
