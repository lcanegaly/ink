#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
//#include "Window.h"
#include <iostream>
#include "Renderer.h"
#include "Shaders.h"
#include "Fractal.h"
//#include "Gui.h"
//#include "MouseInput.h"
#include "glm.hpp"


#define WIDTH 800
#define HEIGHT 600

EM_BOOL one_iter(double time, void* userData);
Fractal* fractal_ptr = nullptr;

GLuint programObject;

GLuint loadShader(GLenum type, const char *source)
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
    //~ glShaderSource(shader, 1, &source, 0);
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


GLuint buildProgram(GLuint vertexShader, GLuint fragmentShader, const char * vertexPositionName)
{
    // create a GL program and link it
    GLuint po = glCreateProgram();
    glAttachShader(po, vertexShader);
    glAttachShader(po, fragmentShader);
    glBindAttribLocation(po, 0, vertexPositionName);
    glLinkProgram(po);

    // check if the program linked successfully
    GLint linked;
    glGetProgramiv(po, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        printf("Program link error\n");
        glDeleteProgram(po);
        return 0;
    }
    return po;
}



GLFWwindow* window = nullptr;
int main()
{



    int width = 640;
    int height = 480;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // OpenGL ES 2.0
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);

    GLuint VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(s_Vertices), s_Vertices, GL_STATIC_DRAW);

    glClearColor(0.65f, 0.45f, 0.65f, 1.0f);

  /*
    const char vertexShaderSource[] = 
    "attribute vec4 vPosition; \n"
    "void main() \n"
    "{ \n"
    "   gl_Position = vPosition; \n"
    "} \n";

    const char fragmentShaderSource[] = 
    "precision mediump float; \n"
    "void main() \n"
    "{ \n"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0), \n"
    "                (0.0 , 1.0 , 0.0 , 1.0),\n"
    "                (0.0 , 0.0 , 0.1 , 1.0); \n"
    "} \n";
*/

    // load vertex and fragment shaders
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource2);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource2);
    programObject = buildProgram(vertexShader, fragmentShader, "vPosition");


	emscripten_request_animation_frame_loop(one_iter, 0);
	//while (!glfwWindowShouldClose(window))
	//while (!Window::ShouldClose())
	//{
		//Window::Clear();

		//fractal.Display();

		//up button
		/*if (gui.Button(40, 40, 80, 80, gui.up_arrow)) 
		{
			fractal.SetBounds(glm::vec2(0.0, 0.1), 0);
		}
		//down button
		if (gui.Button(40, 40, 80, 180, gui.down_arrow))
		{
			fractal.SetBounds(glm::vec2(0.0, -0.1), 0);
		}
		//left button
		if (gui.Button(40, 40, 40, 130, gui.left_arrow))
		{
			fractal.SetBounds(glm::vec2(-0.1, 0.0), 0);
		}
		//right button
		if (gui.Button(40, 40, 120, 130, gui.right_arrow))
		{
			fractal.SetBounds(glm::vec2(0.1, 0.0), 0);
		}
		//zoom in button
		if (gui.Button(40, 40, 160, 80, gui.plus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), 0.1);
		}
		//zoom out button
		if (gui.Button(40, 40, 160, 180, gui.DrawMinus))
		{
			fractal.SetBounds(glm::vec2(0.0, 0.0), -0.1);
		}
		gui.ResetGui();
*/
	//	Window::GetMouseInput(mouse);
	//	gui.AddMouseInputEvent(mouse);
	//}

	return 0;
}

EM_BOOL one_iter(double time, void* userData) {
  // Can render to the screen here, etc.
  std::cout << "test is running" << std::endl;  

    // RENDER

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    

  	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	  //glEnableVertexAttribArray(0);

	  //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	  //glEnableVertexAttribArray(1);


  	//glm::mat4 model = glm::mat4(1.0f);

	  //GLint uniformTranslate = glGetUniformLocation(m_Program, "translate");
	  //glUniformMatrix4fv(uniformTranslate, 1, GL_FALSE, glm::value_ptr(model));

  	//GLint uniformZoom = glGetUniformLocation(m_Program, "zoom");
	  //glUniform1f(uniformZoom, (float)zoom);

	  //GLint uniformPan = glGetUniformLocation(m_Program, "pan");
	  //glUniform2f(uniformPan, center.x, center.y);



    glDrawArrays(GL_TRIANGLES, 0, 6);
    glfwSwapBuffers(window);


  return EM_TRUE;
}


