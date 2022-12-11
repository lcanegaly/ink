#include "Gui.h"
#include <cmath>

Gui::Gui(Renderer& renderer)
	: m_GuiRenderer{ renderer }, m_DefaultHeight{ 32 }, m_DefaultWidth{32}
{
	ResetGui();

  m_Textures[Icons::up_arrow].CreateTexture("up.tga");
  renderer.LoadTexture(m_Textures[Icons::up_arrow].GetTexture(), Icons::up_arrow, 
                       m_Textures[Icons::up_arrow].GetSize().x, m_Textures[Icons::up_arrow].GetSize().y);
  m_Textures[Icons::down_arrow].CreateTexture("down.tga");
  renderer.LoadTexture(m_Textures[Icons::down_arrow].GetTexture(), Icons::down_arrow, 
                       m_Textures[Icons::down_arrow].GetSize().x, m_Textures[Icons::down_arrow].GetSize().y);
  m_Textures[Icons::left_arrow].CreateTexture("left.tga");
  renderer.LoadTexture(m_Textures[Icons::left_arrow].GetTexture(), Icons::left_arrow, 
                       m_Textures[Icons::left_arrow].GetSize().x, m_Textures[Icons::left_arrow].GetSize().y);
  m_Textures[Icons::right_arrow].CreateTexture("right.tga");
  renderer.LoadTexture(m_Textures[Icons::right_arrow].GetTexture(), Icons::right_arrow, 
                       m_Textures[Icons::right_arrow].GetSize().x, m_Textures[Icons::right_arrow].GetSize().y);
  m_Textures[Icons::plus].CreateTexture("plus.tga");
  renderer.LoadTexture(m_Textures[Icons::plus].GetTexture(), Icons::plus, 
                       m_Textures[Icons::plus].GetSize().x, m_Textures[Icons::plus].GetSize().y);
  m_Textures[Icons::minus].CreateTexture("minus.tga");
  renderer.LoadTexture(m_Textures[Icons::minus].GetTexture(), Icons::minus, 
                       m_Textures[Icons::minus].GetSize().x, m_Textures[Icons::minus].GetSize().y);
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
	m_GuiRenderer.Draw(m_Textures[texture].GetTexture(), texture, posX, posY, width, height, rotation);
	if (m_Mouse.m_LeftClick) {
		int x = std::abs(m_Mouse.m_MouseX - posX);
		int y = std::abs(m_Mouse.m_MouseY - posY);

		if ( (x <= 0.5 * width) && ( y <= 0.5 * height ))
		{
      m_Mouse.Clear();
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

