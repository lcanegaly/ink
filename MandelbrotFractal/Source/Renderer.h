#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "glm.hpp"
#include <GLFW/glfw3.h>

class Renderer
{
public:
	Renderer(const Renderer&) = delete;

	static Renderer& Get() {
		static Renderer instance;
		return instance;
	}

	void Init(int width, int height, GLFWwindow* window);
	void DrawFractal(int windowWidth, int windowHeight, glm::vec2 center, double zoom);
	void Draw(unsigned char* tex, int bind_num, int posX, int posY, int width, int height, float rotation = 0);
	void SetActiveTexture(int texSlot);
	void PrintStatus() const;
	void TestDraw(int bind);
  GLuint BuildProgram(GLuint vshader, GLuint fshader, const char* vertexPositionName );
  GLuint LoadShader(GLenum type, const char* shaderSource);
  GLuint CreateSimpleTexture2D();
  void LoadTexture(unsigned char* texture, int bind_num, int width, int height);
    
	glm::vec2 ConvertNormToPixel(glm::vec2 xy);
	glm::vec2 ConvertPixelToNorm(int x, int y);
	
  GLFWwindow* window = nullptr;
private:
	Renderer();
	int m_Width, m_Height;
	GLuint m_VBO;
	unsigned int m_VAO;
	GLuint m_Program;
	GLuint m_MenuProgram;
	GLuint m_Texture[6];
};


static const GLfloat vVertices[9] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
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

