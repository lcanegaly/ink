#pragma once
#include "GL/glew.h"
#include "glm.hpp"
#include <GLFW/glfw3.h>
#include "window.h"
#include "GL/gl.h"

struct ImageData {
  unsigned char* tex; 
  int bind_num; 
  int pos_x; 
  int pos_y; 
  int width; 
  int height;
  float rotation;
  int texture_rows;
  int texture_columns;
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
  void DrawFractal(int window_width, int window_height, glm::vec2 center, double zoom);
	void Draw(unsigned char* tex, int bind_num, int pos_x, int pos_y, int width, int height, float rotation = 0);
	void Draw(ImageData& image_data);
  GLuint BuildProgram(GLuint vertex_shader, GLuint fragment_shader, const char* vertex_position_name );
  GLuint LoadShader(GLenum type, const char* shader_source);
  void LoadTexture(unsigned char* texture, int bind_num, int width, int height);

	glm::vec2 ConvertNormToPixel(glm::vec2 xy);
	glm::vec2 ConvertPixelToNorm(int x, int y);
private:
	Renderer();
	int width_, height_;
	GLuint vbo_;
	unsigned int vao_;
	GLuint program_;
	GLuint menu_program_;
	GLuint texture_[10];
	WindowDelegate* window_ptr_;
};


static const float vertices[30] = {
	// first triangle
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // top right
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f, // top left 
	// second triangle
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f // top left
};
