#include "Gui.h"
#include "targa.h"
#include <cmath>
#include <iostream>
#include <string>
#include <format>
Gui::Gui(Renderer& renderer)
	: m_GuiRenderer{ renderer }, m_DefaultHeight{ 32 }, m_DefaultWidth{32}
{
	ResetGui();

//  printf("Image about to be loaded \n");
//  m_Images[0] = new Image("up.tga", &m_GuiRenderer, 250, 250, 100, 100);
 // printf("New Image Created \n");


  
  //renderer.LoadTexture(m_Images[Icons::up_arrow]->image(), Icons::up_arrow, 
                      // m_Images[Icons::up_arrow]->dimensions().x, m_Images[Icons::up_arrow]->dimensions().y);
 
/*
  m_Images[Icons::down_arrow].LoadImage("down.tga");
  renderer.LoadTexture(m_Images[Icons::down_arrow].image(), Icons::down_arrow, 
                       m_Images[Icons::down_arrow].dimensions().x, m_Images[Icons::down_arrow].dimensions().y);
  m_Images[Icons::left_arrow].LoadImage("left.tga");
  renderer.LoadTexture(m_Images[Icons::left_arrow].image(), Icons::left_arrow, 
                       m_Images[Icons::left_arrow].dimensions().x, m_Images[Icons::left_arrow].dimensions().y);
  m_Images[Icons::right_arrow].LoadImage("right.tga");
  renderer.LoadTexture(m_Images[Icons::right_arrow].image(), Icons::right_arrow, 
                       m_Images[Icons::right_arrow].dimensions().x, m_Images[Icons::right_arrow].dimensions().y);
  m_Images[Icons::plus].LoadImage("plus.tga");
  renderer.LoadTexture(m_Images[Icons::plus].image(), Icons::plus, 
                       m_Images[Icons::plus].dimensions().x, m_Images[Icons::plus].dimensions().y);
  m_Images[Icons::minus].LoadImage("minus.tga");
  renderer.LoadTexture(m_Images[Icons::minus].image(), Icons::minus, 
                       m_Images[Icons::minus].dimensions().x, m_Images[Icons::minus].dimensions().y);
*/
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
	//m_GuiRenderer.Draw(m_Images[texture]->image(), texture, posX, posY, width, height, rotation);
	//Todo.. image draw call here.
  //printf("In Button call \n");
 // m_Images[0]->Draw(width, height, posX, posY); 
  //Object* obj = m_Images[0];
  //obj->Draw(); 
  

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

