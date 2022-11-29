#define GLEW_STATIC
#include <GL/glew.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>

GLfloat vVertices[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};
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

int main(){

    int width = 640;
    int height = 480;

    GLFWwindow* window;

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sizeof(vVertices), vVertices, GL_STATIC_DRAW);

    glClearColor(0.65f, 0.45f, 0.65f, 1.0f);

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

    // load vertex and fragment shaders
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    programObject = buildProgram(vertexShader, fragmentShader, "vPosition");

    // RENDER

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);

    return 0;
}
