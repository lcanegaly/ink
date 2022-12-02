#pragma once

const char vertexShaderSource2[] =
      "attribute vec4 a_position;   \n"
      "attribute vec2 a_texCoord;   \n"
      "varying vec2 v_texCoord;     \n"
	    "uniform mat4 translate;\n"
      "void main()                  \n"
      "{                            \n"
      //"   gl_Position = a_position; \n"
		  "gl_Position = translate * vec4(a_position.x, a_position.y, a_position.z, 1.0);\n"
      "   v_texCoord = a_texCoord;  \n"
      "}                            \n";

const char fragmentShaderSource2[] =  
      "precision mediump float;                            \n"
      "varying vec2 v_texCoord;                            \n"
    	"uniform float zoom;\n"
	    "uniform vec2 pan;\n"
      "void main()                                         \n"
      "{                                                   \n"
     	" vec2 uv = vec2(v_texCoord.x * 3.0, v_texCoord.y*3.0);\n"
		  " uv = uv - vec2(1.5, 1.5);                        \n"
  		"uv *= vec2(zoom);\n"
	  	"uv += pan;"
      " float x = 0.0;\n"
	  	" float y = 0.0;\n"
	  	" float cx = uv.x;\n"
	  	" float cy = uv.y;\n"
	  	" float it = 0.0;\n"
      "for (int z = 0;z < 1000; z++){ \n"
      "if (x*x + y*y <= 2.0*2.0)\n"
	  	"{\n"
		  " float xtemp = x*x - y*y + cx;\n"
			" y = 2.0*x*y + cy;\n"
			" x = xtemp;\n"
			" it = it + 1.0;\n"
		  "}else{\n"
		  "break;\n"
		  "}\n"
		  "}\n"
		  "vec3 col = vec3(1.0*uv.x, 1.0*uv.y, 0.0);\n"
		  "if (it > 501.0)\n"
		  "{\n"
			" col = vec3(0.0, 0.0, 0.0);\n"
		  "}else{\n"
			" col = vec3(0.0, 0.25, 0.1);\n"
			" col = vec3(0.0, 0.25+0.01*it, 0.1*it);\n"
		  "}\n"
		  "gl_FragColor = vec4(col, 1.0);\n"
      "}                                                   \n";

static const char* s_FragmentShaderSourceMenu2
{
  "precision mediump float;                             \n"
  "varying vec2 v_texCoord;                            \n"
	"uniform sampler2D Texture;\n"
	"void main()\n"
	"{\n"
		"gl_FragColor = texture2D(Texture, v_texCoord);\n"
	"}\0"
};

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
  "   gl_FragColor = vec4(1.0, 0.5, 0.2, 1.0); \n"
  "} \n";

static const char* s_VertexShaderSource
{
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aTexCoord;\n"
	"out vec2 TexCoord;\n"
	"uniform mat4 translate;\n"
	"void main()\n"
	"{\n"
		"gl_Position = translate * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"TexCoord = aTexCoord;\n"
	"}\0"
};

static const char* s_FragmentShaderSource
{
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec2 TexCoord;\n"
	"uniform float zoom;\n"
	"uniform vec2 pan;\n"
	"void main()\n"
	"{\n"
		"vec2 uv = vec2(TexCoord.x * 3.0, TexCoord.y*3.0);\n"
		"uv = uv - vec2(1.5, 1.5);\n"

		"uv *= vec2(zoom);\n"
		"uv += pan;"

		"float x = 0.0;\n"
		"float y = 0.0;\n"
		"float cx = uv.x;\n"
		"float cy = uv.y;\n"
		"float it = 0.0;\n"

		"while (x*x + y*y <= 2.0*2.0 && it < 1000.0)\n"
		"{\n"
			"float xtemp = x*x - y*y + cx;\n"
			"y = 2.0*x*y + cy;\n"
			"x = xtemp;\n"
			"it = it + 1.0;\n"
		"}\n"

		"vec3 col = vec3(1.0*uv.x, 1.0*uv.y, 0.0);\n"

		"if (it > 501.0)\n"
		"{\n"
			"col = vec3(0.0, 0.0, 0.0);\n"
		"}else{\n"
			"col = vec3(0.0, 0.25+0.01*it, 0.1*it);\n"
		"}\n"

		"FragColor = vec4(col, 1.0);\n"
	"}\0"
};

static const char* s_FragmentShaderSourceMenu
{
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec2 TexCoord;\n"
	"uniform sampler2D Texture;\n"
	"void main()\n"
	"{\n"
		"FragColor = texture(Texture, TexCoord);\n"
	"}\0"
};
