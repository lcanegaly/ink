
#include "GL/glew.h"
#include "window.h"
#include "renderer.h"
#include <stdio.h>
#include <iostream>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shaders.h"


Renderer::Renderer() 
	: m_Width{ 0 }, m_Height{ 0 }, m_VBO{ 0 }, m_VAO{ 0 }, m_Program{ 0 }, m_MenuProgram{ 0 }, m_Texture{ 0 }
{
};

Renderer::~Renderer(){
  delete window_ptr_;
}
void Renderer::Init(int width, int height, WindowDelegate* window_ptr) //TODO need to pass in window context. 
{
	m_Width = width;
	m_Height = height;
  window_ptr_ = window_ptr;

  GLuint VBO;
  glGenBuffers(1, &VBO);  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);  
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(s_Vertices), s_Vertices, GL_STATIC_DRAW);

  glClearColor(0.65f, 0.45f, 0.65f, 1.0f);

  // load vertex and fragment shaders
  GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource2);
  GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource2);
  m_Program = BuildProgram(vertexShader, fragmentShader, "vPosition");

  //  load fragment shader for menu 
  GLuint fragmentShader2 = LoadShader(GL_FRAGMENT_SHADER, s_FragmentShaderSourceMenu2);
  m_MenuProgram = BuildProgram(vertexShader, fragmentShader2, "iPosition");

  glGenTextures(6, m_Texture);
};

void Renderer::StartDraw()
{
  glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::EndDraw()
{

}
void Renderer::SetClearColor(float r, float g, float b, float a)
{
  glClearColor(r,g,b,a);  
}

void Renderer::DrawFractal(int windowWidth, int windowHeight, glm::vec2 center = glm::vec2(0.0f,0.0f), double zoom = 1.0)
{
  glUseProgram(m_Program);
	glm::mat4 model = glm::mat4(1.0f);

	GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

	GLint uniformZoom = glGetUniformLocation(m_Program, "zoom");
	glUniform1f(uniformZoom, (float)zoom);

	GLint uniformPan = glGetUniformLocation(m_Program, "pan");
	glUniform2f(uniformPan, center.x, center.y);

  glClear(GL_COLOR_BUFFER_BIT);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
    
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glfwSwapBuffers(window_ptr_->context());
}

void Renderer::Draw(unsigned char* tex, int bind_num, int posX, int posY, int width, int height, float rotation)
{
  glUseProgram(m_MenuProgram);
  int textureRows = 1;
  int textureColumns = 1;
  int row = 0;
  int column = 0;
  GLint texture_uniform = glGetUniformLocation ( m_MenuProgram, "Texture" );
  GLint uniformRows = glGetUniformLocation(m_MenuProgram, "rows");
  GLint uniformColumns = glGetUniformLocation(m_MenuProgram, "columns");
  GLint uniformRow = glGetUniformLocation(m_MenuProgram, "row");
  GLint uniformColumn = glGetUniformLocation(m_MenuProgram, "column");
	glUniform1f(uniformRows, (float)textureRows);
	glUniform1f(uniformColumns, (float)textureColumns);
	glUniform1i(uniformRow, row);
	glUniform1i(uniformColumn, column);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindTexture(GL_TEXTURE_2D, m_Texture[bind_num]);
  glUniform1i (texture_uniform, 0 );
  
  glm::vec2 position = ConvertPixelToNorm(posX, posY);
	glm::vec2 size;
	size.x = (float)width / (float)m_Width;
	size.y = (float)height / (float)m_Height;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glfwSwapBuffers(window_ptr_->context());
}

void Renderer::Draw(ImageData& image_data)
{
  glUseProgram(m_MenuProgram);
  GLint texture_uniform = glGetUniformLocation ( m_MenuProgram, "Texture" );
  GLint uniformRows = glGetUniformLocation(m_MenuProgram, "rows");
  GLint uniformColumns = glGetUniformLocation(m_MenuProgram, "columns");
  GLint uniformRow = glGetUniformLocation(m_MenuProgram, "row");
  GLint uniformColumn = glGetUniformLocation(m_MenuProgram, "column");
	glUniform1f(uniformRows, (float)image_data.textureRows);
	glUniform1f(uniformColumns, (float)image_data.textureColumns);
	glUniform1i(uniformRow, image_data.row);
	glUniform1i(uniformColumn, image_data.column);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  glBindTexture(GL_TEXTURE_2D, m_Texture[image_data.bind_num]);
  glUniform1i (texture_uniform, 0 );
  
  glm::vec2 position = ConvertPixelToNorm(image_data.posX, image_data.posY);
	glm::vec2 size;
	size.x = (float)image_data.width / (float)m_Width;
	size.y = (float)image_data.height / (float)m_Height;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::rotate(model, glm::radians(image_data.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

  glDrawArrays(GL_TRIANGLES, 0, 6);
  glfwSwapBuffers(window_ptr_->context());
}

void Renderer::LoadTexture(unsigned char *texture, int bind_num, int width, int height){
  glBindTexture(GL_TEXTURE_2D, m_Texture[bind_num]);

  //set texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture); 
}

GLuint Renderer::LoadShader(GLenum type, const char* source)
{
    // create shader
    GLuint shader = glCreateShader(type);
    if(shader == 0)
    {
        printf("Error creating shader\n");
        return 0;
    }

    // load the shader source to the shader object and compile it;
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // check if the shader compiled successfully
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        printf("Shader compilation error\n");
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint Renderer::BuildProgram(GLuint vertexShader, GLuint fragmentShader, const char * vertexPositionName)
{
   // create a GL program and link it
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program, 0, vertexPositionName);
    glLinkProgram(program);

    // check if the program linked successfully
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        printf("Program link error\n");
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

glm::vec2 Renderer::ConvertNormToPixel(glm::vec2 xy)
{
	float outX = ((xy.x + 1.0f) / 2.0f) * m_Width;
	float outY = ((xy.y + 1.0f) / 2.0f) * m_Height;
	outY = outY * -1; //flip y for drawing
	return glm::vec2(outX, outY);
}

glm::vec2 Renderer::ConvertPixelToNorm(int x, int y)
{
	float outX = (((float)x / (float)m_Width)*2) - 1;
	float outY = (((float)y / (float)m_Height) * 2) - 1;
	outY = outY * -1; //flip y for drawing

	return glm::vec2(outX, outY);
}

