#ifndef SHADERS_H
#define SHADERS_H

#include "../core/utils.h"

static inline u32 ast_compile_shader(GLenum type, const char *source) {
  u32 shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  // Check for compilation errors
  i32 success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    LOG_ERROR("Shader Compilation Failed\n%s\n", infoLog);
  }

  return shader;
}

static inline u32 ast_create_shader(const char *vertex_code, const char *fragment_code) {
  // if code is null, return 0
  if (!vertex_code || !fragment_code) return 0;
  
  // Compile vertex and fragment shaders
  u32 vertex_shader   = ast_compile_shader(GL_VERTEX_SHADER, vertex_code);
  u32 fragment_shader = ast_compile_shader(GL_FRAGMENT_SHADER, fragment_code);

  // Create shader program and link shaders
  u32 shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  // Check for linking errors
  i32 success;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    LOG_ERROR("Shader Program Linking Failed\n%s\n", infoLog);
  }

  // Clean up shaders as they're now linked into the program
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return shader_program;
}

//------------------------------------------------------------------------------------------------
// Core Shader Library - Multiple Shaders Code
// doing strange macro and struc trick (maybe problems ?)

#define GLSL(src) "#version 330 core\n" #src
#define WEBGL(src) #src

typedef struct ast_shader_container {
  const char* default_vert_shader;
  const char* default_frag_shader;
  const char* web_default_vert_shader;
  const char* web_default_frag_shader; 
} ast_shader_container;

static ast_shader_container ast_shader_lib = {
  
  .default_vert_shader = GLSL(
    layout (location = 0) in vec3 a_pos;
    layout (location = 1) in vec2 a_uvs;

    out vec2 uvs;

    uniform mat4 projection;
    uniform mat4 model;

    void main() {
        uvs = a_uvs;
        gl_Position = projection * model * vec4(a_pos, 1.0);
    }
  ),

  .default_frag_shader = GLSL(
    out vec4 frag_color;
    in  vec2 uvs;

    uniform vec4      color;
    uniform sampler2D texture_id;

    void main() {
      vec2 center = vec2(0.5, 0.5); // Center of the UV space
      float distance = length(uvs - center);

      float circle_radius   = 0.5;
      float edge_smoothness = 0.01;

      float alpha = smoothstep(circle_radius - edge_smoothness, circle_radius, distance);
      frag_color = vec4(color.rgb, (1.0 - alpha) * color.a);
    }
  ),
  
  // .default_frag_shader = GLSL(
  //   out vec4 frag_color;
  //   in  vec2 uvs;
  //
  //   uniform vec4      color;
  //   uniform sampler2D texture_id;
  //
  //   void main() {
  //     frag_color = texture(texture_id, uvs) * color;
  //   }
  // ),
 
  .web_default_vert_shader = WEBGL(
    attribute vec3 a_pos;
    attribute vec2 a_uvs;
    varying   vec2 uvs;
    uniform   mat4 projection;
    uniform   mat4 model;

    void main() {
      uvs = a_uvs;
      gl_Position = projection * model * vec4(a_pos, 1.0);
    }
  ),

  .web_default_frag_shader = WEBGL(
    precision mediump float;
    varying   vec2 uvs;
    uniform   sampler2D texture_id;
    uniform   vec4 color;
    
    void main() {
      gl_FragColor = texture2D(texture_id, uvs) * color;
    }
  ),

};

#endif
