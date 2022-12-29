#pragma once
#include "glm.hpp"
#include "Renderer.h"
#include "Texture.h"
#include "object.h"
#include <complex>




class Fractal : public Object {
public:
	Fractal(glm::vec2 screenSize, glm::vec2 centerPoint, Renderer* renderer);
	//sets the coordinate plane bounds
	void SetBounds(glm::vec2 centerPoint, double zoom);
	void Display() const;
  void Draw() override;
  void Update() override;
  void Up() { SetBounds(glm::vec2(0.0, 0.1), 0); }
  void Down() {	SetBounds(glm::vec2(0.0, -0.1), 0); }
  void Left() { SetBounds(glm::vec2(-0.1, 0.0), 0); }
  void Right() { SetBounds(glm::vec2(0.1, 0.0), 0); }
  void In() { SetBounds(glm::vec2(0.0, 0.0), 0.1); }
  void Out() { SetBounds(glm::vec2(0.0, 0.0), -0.1); }
private:
	double m_Zoom;
	const double m_IterationLimit = 500;
	bool m_Calculated;
	glm::vec2 m_ScreenSize;
	glm::vec2 m_CenterPoint;
	Renderer* m_Renderer = nullptr;

};
