#pragma once
#include "GL/glew.h"
#include "glm.hpp"
#include <GLFW/glfw3.h>
#include "window.h"
#include "GL/gl.h"

struct ImageData {
  unsigned char* tex; 
  int bind_num; 
  int posX; 
  int posY; 
  int width; 
  int height;
  float rotation;
  int textureRows;
  int textureColumns;
  int row;
  int column;
};

class Renderer
{
public:
	Renderer(const Renderer&) = delete;
	static Renderer& Get() {
		static Renderer instance;
		return instance;
	}
  ~Renderer(); 
  void Init(int width, int height, WindowDelegate* window);
  void StartDraw();
  void EndDraw();
  void SetClearColor(float r, float g, float b, float a);
  void DrawFractal(int windowWidth, int windowHeight, glm::vec2 center, double zoom);
	void Draw(unsigned char* tex, int bind_num, int posX, int posY, int width, int height, float rotation = 0);
	void Draw(ImageData& image_data);
  GLuint BuildProgram(GLuint vshader, GLuint fshader, const char* vertexPositionName );
  GLuint LoadShader(GLenum type, const char* shaderSource);
  void LoadTexture(unsigned char* texture, int bind_num, int width, int height);

	glm::vec2 ConvertNormToPixel(glm::vec2 xy);
	glm::vec2 ConvertPixelToNorm(int x, int y);
private:
	Renderer();
	int m_Width, m_Height;
	GLuint m_VBO;
	unsigned int m_VAO;
	GLuint m_Program;
	GLuint m_MenuProgram;
	GLuint m_Texture[10];
	WindowDelegate* window_ptr_;
};


static const float s_Vertices[30] = {
	// first triangle
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // top right
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left 
	// second triangle
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f // top left
};

