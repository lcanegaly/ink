#pragma once
#include "Renderer.h"
#include "image.h"
#include "MouseInput.h"

class Gui
{
public:
	Gui(Renderer& renderer);
	~Gui();

	void AddMouseInputEvent(int button, int action, double xpos, double ypos);
	void AddMouseInputEvent(MouseInput& m);
	bool Button(int width, int height, int posX, int posY, int texture, float rotation = 0);
	void ResetGui();
//  void DrawGui();
  enum Icons {up_arrow, down_arrow, left_arrow, right_arrow, minus, plus};

private:
	Renderer& m_GuiRenderer;
	const static int m_NumTextures = 6;
	bool m_IsDrawn = false;
	MouseInput m_Mouse;
	Image* m_Images[m_NumTextures];
	int m_DefaultWidth;
	int m_DefaultHeight;
};

