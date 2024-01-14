#pragma once
#include <memory>
#include <vector>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "window.h"
#include "GL/gl.h"
#include "transform.h"
#include "vertex.h"
#include "camera.h"

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
  void Draw(Transform transform, unsigned int vao, int indices ); 
  void Draw(ImageData& image_data);
  glm::vec2 ConvertNormToPixel(glm::vec2 xy);
  glm::vec2 ConvertPixelToNorm(int x, int y);
  glm::vec3 RayCast(glm::vec3 origin, glm::vec3 direction, int distance); 
  glm::vec2 ScreenToNDC(glm::vec2 screen_coord, int screen_width, int screen_height);
  GLuint LoadTexture(unsigned char* texture, int width, int height,
      int color_depth);
  unsigned int VertexArray(); 
  void DrawWireframe(bool enable);
  unsigned int UploadMesh(std::vector<Vertex> vert, std::vector<unsigned int> index);
  glm::mat4 GetViewProjMaxtrix(){
    return view_proj_matrix_;
    //return glm::perspective(65.0f, 800.0f/600.0f, 0.1f, 5000.0f)
    //  * camera_.GetViewMatrix();;
    //return glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 5000.0f);
  }
  Camera& GetCamera(){
    return camera_; 
  }
  void SetModeOrtho(){
    projMatrix_ = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 5000.0f);
  }
  void SetModePerspective(){
    projMatrix_ = glm::perspective(45.0f, 1280.0f/800.0f, 0.1f, 1500.0f);
  }

 private:
  GLuint BuildProgram(GLuint vertex_shader, GLuint fragment_shader, const char* vertex_position_name );
  GLuint LoadShader(GLenum type, const char* shader_source);

 private:
	Renderer();
  glm::mat4 projMatrix_ = glm::perspective(45.0f, 800.0f/600.0f, 0.0f, 5000.0f);
  glm::mat4 view_proj_matrix_;
	int width_, height_;
	GLuint vbo_;
	GLuint ebo_;
	unsigned int vao_;
	GLuint program_;
	GLuint texture_;
  WindowDelegate* window_ptr_;
  Camera camera_;
};
