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

#endif
