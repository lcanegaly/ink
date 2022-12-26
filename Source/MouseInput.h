#pragma once

struct MouseInput
{
	double m_MouseX;
	double m_MouseY;
	bool m_LeftClick;
	bool m_RightClick;

	MouseInput()
		: m_MouseX{ 0 }, m_MouseY{ 0 }, m_LeftClick{ false }, m_RightClick{ false }
	{};

	void Clear() 
	{
		m_MouseX = 0; 
		m_MouseY = 0; 
		m_LeftClick = false; 
		m_RightClick = false; 
	};
};