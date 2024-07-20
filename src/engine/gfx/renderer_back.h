#ifndef RENDERER_BACK_H
#define RENDERER_BACK_H

#include "../core/utils.h"
#include "../core/window.h"

#include "../math/linalg.h"
#include "shaders.h"

typedef struct {
  u32 vao_quad;
  u32 vbo_quad;
  u32 ebo_quad;
 
  u32 shader_default;
  u32 texture_color;
  ast_mat4 proj;
} ast_Renderer;


static inline void ast_init_shaders(ast_Renderer *renderer, i32 render_width, i32 render_height);
static inline void ast_init_color_textures(u32 *texture_color);
static inline void ast_init_quad(u32 *vao, u32 *vbo, u32 *ebo);

static inline ast_Renderer *ast_init_renderer(i32 render_width, i32 render_height) {
  ast_Renderer *renderer = (ast_Renderer*) malloc(sizeof(ast_Renderer)); 
  LOG_INFO("Render Texture Size: %dx%d\n", render_width, render_height);

  ast_init_shaders(renderer, render_width, render_height);
  ast_init_color_textures(&renderer->texture_color);
  ast_init_quad(&renderer->vao_quad, &renderer->vbo_quad, &renderer->ebo_quad);
  return renderer;
}

static inline void ast_init_shaders(ast_Renderer *renderer, i32 render_width, i32 render_height) {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  #ifdef WEB_BUILD
    renderer->shader_default = ast_create_shader(ast_shader_lib.web_default_vert_shader, ast_shader_lib.web_default_frag_shader); 
  #else
    renderer->shader_default = ast_create_shader(ast_shader_lib.default_vert_shader, ast_shader_lib.default_frag_shader);
  #endif

  renderer->proj = ast_mat4_ortho(0, render_width, 0, render_height, -2, 2);

  glUseProgram(renderer->shader_default);
  glUniformMatrix4fv(glGetUniformLocation(renderer->shader_default, "projection"), 1, GL_FALSE, ast_mat4_opengl(&renderer->proj));  
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
