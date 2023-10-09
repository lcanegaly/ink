
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <stdio.h>
#include <vector>

#include "GL/glew.h"
#include "window.h"
#include "renderer.h"
#include "shaders.h"
#include "transform.h"
#include <iostream>
Renderer::Renderer() 
	: width_{ 0 }, height_{ 0 }, vbo_{ 0 }, vao_{ 0 }, program_{ 0 }, texture_{ 0 }
{};

Renderer::~Renderer() {}

void Renderer::Init(int width, int height, WindowDelegate* window_ptr) {
	width_ = width;
	height_ = height;
  window_ptr_ = window_ptr;
  glGenVertexArrays(1, &vao_);  
  glBindVertexArray(vao_); 
  glGenBuffers(1, &vbo_);  
  glGenBuffers(1, &ebo_);  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(vertices), vertices, GL_STATIC_DRAW);

  glClearColor(0.65f, 0.45f, 0.65f, 1.0f);
  glGenTextures(6, texture_);
};

void Renderer::StartDraw() {
  glClear(GL_COLOR_BUFFER_BIT);
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

unsigned int Renderer::VertexArray() {
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  glGenVertexArrays(1, &vao);  
  glGenBuffers(1, &vbo);  
  glGenBuffers(1, &ebo);  
  const float vertices [] = {
    // front face 
    0.5f,  0.5f, 0.5f, 1.0f, 1.0f,  //0 top right
	  0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  //1 bottom right
	  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, //2 bottom left
	  -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, //3 top left 
    // back face 
    0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  //4 top right
	  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, //5 bottom right
	  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //6 bottom left
	  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, //7 top left 
  };
  
  unsigned int indices [] = {
    0,1,3,
    1,2,3,
    2,3,7,
    2,6,7,
    4,5,7,
    5,6,7,
    4,0,5,
    1,0,5,
    0,3,4,
    3,7,4,
    1,2,5,
    2,6,5
  };

  glBindVertexArray(vao);  
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0); 
  return vao;
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
  glBindTexture(GL_TEXTURE_2D, texture_[bind_num]);
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

// TODO should load from file
void Renderer::LoadShader(){
  GLuint vertex_shader = LoadShader(GL_VERTEX_SHADER, vertex_shader_source2);
  GLuint fragment_shader = LoadShader(GL_FRAGMENT_SHADER, fragment_shader_source2);
  program_ = BuildProgram(vertex_shader, fragment_shader, "iPosition");
 }

void Renderer::Draw(Transform2D transform, unsigned int vao, int indices) {
  glUseProgram(program_);
  glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
	model = glm::rotate(model, glm::radians(glm::degrees(transform.x.x)), glm::vec3(1.0f, 0.2f, 0.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(40.0f), (float)width_/(float)height_, 0.1f, 100.0f);
  model = projection * model; 
  GLint uniform_translate = glGetUniformLocation(program_, "translate");
	glUniformMatrix4fv(uniform_translate, 1, GL_FALSE, glm::value_ptr(model));

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
  glBindTexture(GL_TEXTURE_2D, texture_[image_data.bind_num]);
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

void Renderer::LoadTexture(unsigned char *texture, int bind_num, int width, int height, int color_depth) {
  glBindTexture(GL_TEXTURE_2D, texture_[bind_num]);
  // set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (color_depth == 3) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture); 
  }
  else{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture); 
  }
}

GLuint Renderer::LoadShader(GLenum type, const char* source) {
  // create shader
  GLuint shader = glCreateShader(type);
  if(shader == 0) {
    printf("Error creating shader\n");
    return 0;
  }
  // load the shader source to the shader object and compile it;
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  // check if the shader compiled successfully
  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    printf("Shader compilation error\n");
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
    glDeleteShader(shader);
    for (auto x : infoLog){
      std::cout << x;
    }
    std::cout << "\n";
    return 0;
  }
  return shader;
}

GLuint Renderer::BuildProgram(GLuint vertex_shader, GLuint fragment_shader, 
  const char * vertex_position_name) {
  // create a GL program and link it
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glBindAttribLocation(program, 0, vertex_position_name);
  glLinkProgram(program);
  // check if the program linked successfully
  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if(!linked) {
    printf("Program link error\n");
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);
    for (auto x : infoLog){
      std::cout << x;
    }
    std::cout << "\n";
    return 0;
  }
  return program;
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

