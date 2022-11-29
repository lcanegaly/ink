#include "Gui.h"
#include <cmath>

Gui::Gui(Renderer& renderer)
	: m_GuiRenderer{ renderer }, m_DefaultHeight{ 40 }, m_DefaultWidth{40}
{
	ResetGui();
	for (int i = 0; i < m_NumTextures; ++i) {
		m_Textures[i].CreateTexture(glm::vec2(m_DefaultWidth, m_DefaultHeight));
		for (int x = 0; x < (m_DefaultWidth * m_DefaultHeight); ++x)
		{
			m_Textures[i].SetPixelColor(glm::vec3(0, 255, 0));
		}
	}
	//create button textures to be used with Gui object
	//up DrawArrow
	m_Textures[Icons::up_arrow].DrawArrow(m_DefaultWidth / 2, m_DefaultHeight - (m_DefaultHeight / 4), m_DefaultWidth / 2, m_DefaultHeight / 2);
	//down DrawArrow
	m_Textures[Icons::down_arrow].DrawArrow(m_DefaultWidth / 2, m_DefaultHeight - (m_DefaultHeight / 4), m_DefaultWidth / 2, m_DefaultHeight / 2);
	m_Textures[Icons::down_arrow].SetRotation(180.0f);
	//left DrawArrow
	m_Textures[Icons::left_arrow].DrawArrow(m_DefaultWidth / 2, m_DefaultHeight - (m_DefaultHeight / 4), m_DefaultWidth / 2, m_DefaultHeight / 2);
	m_Textures[Icons::left_arrow].SetRotation(90.0f);
	//right DrawArrow
	m_Textures[Icons::right_arrow].DrawArrow(m_DefaultWidth / 2, m_DefaultHeight - (m_DefaultHeight / 4), m_DefaultWidth / 2, m_DefaultHeight / 2);
	m_Textures[Icons::right_arrow].SetRotation(-90.0f);
	//DrawMinus
	m_Textures[Icons::DrawMinus].DrawMinus(m_DefaultWidth/2, m_DefaultHeight - (m_DefaultHeight / 2), m_DefaultWidth/ 2, m_DefaultHeight / 2);
	//plus
	m_Textures[Icons::plus].DrawPlus(m_DefaultWidth / 2, m_DefaultHeight - (m_DefaultHeight / 2), m_DefaultWidth / 2, m_DefaultHeight / 2);
}

Gui::~Gui()
{
}

void Gui::AddMouseInputEvent(int button, int action, double xpos, double ypos)
{

	(button == 0 && action == 1) ? m_Mouse.m_LeftClick = true : m_Mouse.m_LeftClick = false;
	(button == 1 && action == 1) ? m_Mouse.m_RightClick = true : m_Mouse.m_RightClick = false;
	m_Mouse.m_MouseX = xpos;
	m_Mouse.m_MouseY = ypos;

}

void Gui::AddMouseInputEvent(MouseInput& m)
{
	m_Mouse = m;
}

bool Gui::Button(int width, int height, int posX, int posY, int texture, float rotation)
{
	m_GuiRenderer.Draw(m_Textures[texture].GetTexture(), posX, posY, width, height, m_Textures[texture].GetRotation());

	if (m_Mouse.m_LeftClick) {
		int x = std::abs(m_Mouse.m_MouseX - posX);
		int y = std::abs(m_Mouse.m_MouseY - posY);

		if ( (x <= 0.5 * width) && ( y <= 0.5 * height ))
		{
			return true;
		}
	}
	return false;
}

void Gui::ResetGui()
{
	m_IsDrawn = false;
	m_Mouse.Clear();
}

