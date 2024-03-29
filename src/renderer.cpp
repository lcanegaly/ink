
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stdio.h>
#include <vector>

#include "objimp/obj.h"
#include "GL/glew.h"
#include "window.h"
#include "renderer.h"
#include "shaders.h"
#include "transform.h"
#include <iostream>
#include "vertex.h"

Renderer::Renderer() 
	: width_{ 0 }, height_{ 0 }, vbo_{ 0 }, vao_{ 0 }, program_{ 0 }, texture_{ 0 }
{};

Renderer::~Renderer() {}

void Renderer::Init(int width, int height, WindowDelegate* window_ptr) {
	width_ = width;
	height_ = height;
  window_ptr_ = window_ptr;
  
  glClearColor(0.25, 0.501, 0.749, 1.0);
  glGenTextures(1, &texture_);
  glEnable(GL_DEPTH_TEST);
};

void Renderer::StartDraw() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  view_proj_matrix_ = projMatrix_ * camera_.GetViewMatrix();
}

void Renderer::EndDraw() {
  glfwSwapBuffers(&window_ptr_->context());
}

void Renderer::SetClearColor(float r, float g, float b, float a) {
  glClearColor(r,g,b,a);  
}

void Renderer::DrawWireframe(bool enable){
  if(enable)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

unsigned int Renderer::UploadMesh(objimp::Mesh mesh){
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  glGenVertexArrays(1, &vao);  
  glGenBuffers(1, &vbo);  
  glGenBuffers(1, &ebo);  
  
  glBindVertexArray(vao);  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh.Indices.size(), &mesh.Indices[0], GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.size() * sizeof(float) * 5, &mesh.Vertices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0); 
  return vao;
}

unsigned int Renderer::UploadMesh(std::vector<Vertex> vert, std::vector<unsigned int> index){
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  glGenVertexArrays(1, &vao);  
  glGenBuffers(1, &vbo);  
  glGenBuffers(1, &ebo);  
  
  glBindVertexArray(vao);  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index[0], GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(float) * 5, &vert[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0); 
  return vao;
}

glm::vec3 Renderer::RayCast(glm::vec3 origin, glm::vec3 direction, int distance){
  return origin + (direction * glm::vec3(distance)); 
} 

glm::vec2 Renderer::ScreenToNDC(glm::vec2 screen_coord, int screen_width, int screen_height) {
// going from NDC to screen..
// NDC i -1 to 1, screen is 0 to width or height etc.
// xpos = x * width/2 + width/2 
// ypos = y * height/2 + height/2
// xpos - (width/2) = x * width/2
// xpos - (width/2) / (width/2) = x
// 2 * xpos - width / width = x
// 2 * ypos - height / height = y
  double screen_x = (2.0f * screen_coord.x - (double)screen_width)  / (double)screen_width; 
  double screen_y = (2.0f * screen_coord.y - (double)screen_height)  / (double)screen_height; 
  return glm::vec2(screen_x, screen_y); 
}

void Renderer::Draw(unsigned char* tex, int bind_num, int pos_x, int pos_y, int width, int height, float rotation) {
  glUseProgram(program_);
  int texture_rows = 1;
  int texture_columns = 1;
  int row = 0;
  int column = 0;
  GLint texture_uniform = glGetUniformLocation ( program_, "Texture" );
  GLint uniform_rows = glGetUniformLocation(program_, "rows");
  GLint uniform_columns = glGetUniformLocation(program_, "columns");
  GLint uniform_row = glGetUniformLocation(program_, "row");
  GLint uniform_column = glGetUniformLocation(program_, "column");
	glUniform1f(uniform_rows, (float)texture_rows);
	glUniform1f(uniform_columns, (float)texture_columns);
	glUniform1i(uniform_row, row);
	glUniform1i(uniform_column, column);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  //glBindTexture(GL_TEXTURE_2D, texture_[bind_num]);
  glUniform1i (texture_uniform, 0 );
  
  glm::vec2 position = ConvertPixelToNorm(pos_x, pos_y);
	glm::vec2 size;
	size.x = (float)width / (float)width_;
	size.y = (float)height / (float)height_;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	GLint uniform_translate = glGetUniformLocation(program_, "translate");
	glUniformMatrix4fv(uniform_translate, 1, GL_FALSE, glm::value_ptr(model));

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Draw(Transform transform, unsigned int vao, int indices) {
  glBindVertexArray(vao);  
  glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(ImageData& image_data) {
  glUseProgram(program_);
  GLint texture_uniform = glGetUniformLocation ( program_, "Texture" );
  GLint uniform_rows = glGetUniformLocation(program_, "rows");
  GLint uniform_columns = glGetUniformLocation(program_, "columns");
  GLint uniform_row = glGetUniformLocation(program_, "row");
  GLint uniform_column = glGetUniformLocation(program_, "column");
	glUniform1f(uniform_rows, (float)image_data.texture_rows);
	glUniform1f(uniform_columns, (float)image_data.texture_columns);
	glUniform1i(uniform_row, image_data.row);
	glUniform1i(uniform_column, image_data.column);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  //glBindTexture(GL_TEXTURE_2D, texture_[image_data.bind_num]);
  glUniform1i(texture_uniform, 0 );
  
  glm::vec2 position = ConvertPixelToNorm(image_data.pos_x, image_data.pos_y);
	glm::vec2 size;
	size.x = (float)image_data.width / (float)width_;
	size.y = (float)image_data.height / (float)height_;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(image_data.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	GLint uniform_translate = glGetUniformLocation(program_, "translate");
	glUniformMatrix4fv(uniform_translate, 1, GL_FALSE, glm::value_ptr(model));

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint Renderer::LoadTexture(unsigned char *texture, int width, int height, int color_depth) {
  glGenTextures(1, &texture_);
  glActiveTexture(GL_TEXTURE0); 
  glBindTexture(GL_TEXTURE_2D, texture_);
  // set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (color_depth == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture); 
  }
  else{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture); 
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  return texture_;
}

glm::vec2 Renderer::ConvertNormToPixel(glm::vec2 xy) {
	float out_x = ((xy.x + 1.0f) / 2.0f) * width_;
	float out_y = ((xy.y + 1.0f) / 2.0f) * height_;
	out_y = out_y * -1; //flip y for drawing
	return glm::vec2(out_x, out_y);
}

glm::vec2 Renderer::ConvertPixelToNorm(int x, int y) {
	float out_x = (((float)x / (float)width_)*2) - 1;
	float out_y = (((float)y / (float)height_) * 2) - 1;
	out_y = out_y * -1; //flip y for drawing
	return glm::vec2(out_x, out_y);
}

