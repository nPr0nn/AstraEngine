#ifndef RENDERER_BACK_H
#define RENDERER_BACK_H

#include "../core/io.h"
#include "../core/utils.h"
#include "../core/window.h"

#include "../math/linmath.h"
#include "../math/linalg.h"
#include "shaders.h"

typedef struct {
  u32 vao_quad;
  u32 vbo_quad;
  u32 ebo_quad;

  u32 shader_default;
  u32 texture_color;
  // ast_mat4 projection;
  mat4x4 projection; 
} ast_Renderer;


static inline void ast_init_shaders(ast_Renderer *renderer, i32 screen_width, i32 screen_height);
static inline void ast_init_color_textures(u32 *texture_color);
static inline void ast_init_quad(u32 *vao, u32 *vbo, u32 *ebo);

static inline ast_Renderer *ast_init_renderer(ast_Window *window) {
  ast_Renderer *renderer = (ast_Renderer*) malloc(sizeof(ast_Renderer));
  i32 screen_width, screen_height;
  ast_get_window_size(window, &screen_width, &screen_height);
  LOG_INFO("Window Size: %dx%d\n", screen_width, screen_height);

  ast_init_shaders(renderer, screen_width, screen_height);
  ast_init_color_textures(&renderer->texture_color);
  ast_init_quad(&renderer->vao_quad, &renderer->vbo_quad, &renderer->ebo_quad);
  return renderer;
}


static inline void ast_init_shaders(ast_Renderer *renderer, i32 screen_width, i32 screen_height) {
  ast_file frag_shader_file = ast_io_file_read("src/engine/gfx/shaders_files/frag_default.glsl");
  ast_file vert_shader_file = ast_io_file_read("src/engine/gfx/shaders_files/vert_default.glsl");

  renderer->shader_default = ast_create_shader(vert_shader_file.data, frag_shader_file.data);
  free(frag_shader_file.data);
  free(vert_shader_file.data);
  
  // ast_mat4 projection = ast_mat4_ortho(0, screen_width, 0, screen_height, -2, 2);
  mat4x4_ortho(renderer->projection, 0, screen_width, 0, screen_height, -2, 2); 
  // renderer->projection = projection;

  glUseProgram(renderer->shader_default);
  glUniformMatrix4fv(glGetUniformLocation(renderer->shader_default, "projection"), 1, GL_FALSE, &renderer->projection[0][0]);
  
  return;
}

static inline void ast_init_color_textures(u32 *texture_color) {
  glGenTextures(1, texture_color);
  glBindTexture(GL_TEXTURE_2D, *texture_color);
  
  u8 solid_white[4] = {255, 255, 255, 255};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  return;
}

static inline void ast_init_quad(u32 *vao, u32 *vbo, u32 *ebo) {
  //     x,    y, z, u, v
  f32 vertices[] = {
       0.5,  0.5, 0, 0, 0,
       0.5, -0.5, 0, 0, 1,
      -0.5, -0.5, 0, 1, 1,
      -0.5,  0.5, 0, 1, 0
  };
  u32 indices[] = {
      0, 1, 3,
      1, 2, 3
  };

  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);
  glGenBuffers(1, ebo);

  glBindVertexArray(*vao);

  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // x, y, z
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
  glEnableVertexAttribArray(0);

  // u, v
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void *)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);
  glBindVertexArray(0);
}

#endif
