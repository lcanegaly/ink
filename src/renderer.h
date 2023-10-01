#pragma once
#include <memory>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "window.h"
#include "GL/gl.h"
#include "transform.h"

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
	void Draw(unsigned char* tex, int bind_num, int pos_x, int pos_y, int width, 
      int height, float rotation = 0);
  void LoadShader();
  void Draw(Transform2D transform ); 
  void Draw(ImageData& image_data);
  glm::vec2 ConvertNormToPixel(glm::vec2 xy);
  glm::vec2 ConvertPixelToNorm(int x, int y);
  void LoadTexture(unsigned char* texture, int bind_num, int width, int height,
      int color_depth);
 
 private:
  GLuint BuildProgram(GLuint vertex_shader, GLuint fragment_shader, const char* vertex_position_name );
  GLuint LoadShader(GLenum type, const char* shader_source);

 private:
	Renderer();
	int width_, height_;
	GLuint vbo_;
	unsigned int vao_;
	GLuint program_;
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

