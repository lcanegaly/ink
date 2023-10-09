#pragma once
static const char* vertex_shader_source2 = {
  "#version 330 core                                      \n"
  "attribute vec4 a_position;                                      \n"
	"uniform mat4 translate;                                         \n"
  "out vec4 pos;                                        \n"
  "void main()                                                     \n"
  "{                                                               \n"
	"   gl_Position = translate * vec4(a_position.x, a_position.y, a_position.z, a_position.a);\n"
  "   pos = a_position;                                     \n"
  "}                                                               \0"
};

static const char * fragment_shader_source2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec4 pos;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.6f, 0.5f - (pos.z * 0.3), 0.2f + (pos.z * 0.3), 1.0f);\n"
    "}\n\0";


//shaders updated to work with webGL/emscripten
static const char* vertex_shader_source = {
  "attribute vec4 a_position;                                      \n"
  "attribute vec2 a_texCoord;                                      \n"
  "varying vec2 v_texCoord;                                        \n"
	"uniform mat4 translate;                                         \n"
  
  "void main()                                                     \n"
  "{                                                               \n"
	"gl_Position = translate * vec4(a_position.x, a_position.y, a_position.z, 1.0);\n"
  "   v_texCoord = a_texCoord;                                     \n"
  "}                                                               \0"
};

static const char* fragment_shader_source = {
  "precision mediump float;                                        \n"
  "varying vec2 v_texCoord;                                        \n"
  "uniform sampler2D Texture;                                      \n"
  "uniform float rows;                                             \n"
  "uniform float columns;                                          \n"
  "uniform int row;                                                \n"
  "uniform int column;                                             \n"
  
  "void main()                                                     \n"
	"{                                                               \n"
	"  vec2 scale = vec2((1.0/columns),(1.0/rows));                  \n"
	"  vec2 imageSection = (v_texCoord + vec2(column, row)) * scale; \n"
	"  vec4 texture_color = texture2D(Texture, imageSection);        \n"
	"  if (texture_color.a < 0.1)                                    \n"
	"     discard;                                                   \n"
	"  gl_FragColor = texture_color;                                 \n"
	"}                                                               \0"
};



