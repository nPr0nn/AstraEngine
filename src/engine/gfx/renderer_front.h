#ifndef RENDERER_FRONT_H
#define RENDERER_FRONT_H

#include "../core/utils.h"
#include "renderer_back.h"

#include "../math/shapes.h"

// Colors Structs and funcs ----------------------------------------
typedef struct ast_color {
  u8 r; u8 g; u8 b; u8 a;
} ast_color;
typedef struct ast_fcolor {
  f32 r; f32 g; f32 b; f32 a;
} ast_fcolor;

static inline ast_fcolor ast_convert_fcolor(ast_color color) {
  return (ast_fcolor){(f32)color.r / 255.0f, (f32)color.g / 255.0f, (f32)color.b / 255.0f, (f32)color.a / 255.0f};
}
static inline ast_color ast_convert_color(ast_fcolor color) {
  return (ast_color){(u8)(color.r * 255.0f), (u8)(color.g * 255.0f), (u8)(color.b * 255.0f), (u8)(color.a * 255.0f)};
}

// Renderer Functions ----------------------------------------------
static inline void ast_render_rect(ast_Renderer *renderer, ast_rect *rect, ast_color color) {
  ast_fcolor fcolor = ast_convert_fcolor(color); 
  f32 c[4] = {fcolor.r, fcolor.g, fcolor.b, fcolor.a};
  
  glUseProgram(renderer->shader_default);
 
  ast_mat4 translation = ast_mat4_translate(rect->x, rect->y, 0);
  ast_mat4 scale       = ast_mat4_scale(rect->w, rect->h, 1);
  ast_mat4 rotate      = ast_mat4_rotate_z(DEG2RAD(35.6));
  ast_mat4 model       = ast_mat4_compose(scale, rotate, translation);  

  glUniformMatrix4fv(glGetUniformLocation(renderer->shader_default, "model"), 1, GL_FALSE, ast_mat4_opengl(&model));
  glUniform4fv(glGetUniformLocation(renderer->shader_default, "color"), 1, c); 
 
  glBindVertexArray(renderer->vao_quad);

  glBindTexture(GL_TEXTURE_2D, renderer->texture_color);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0); 
}

#endif
