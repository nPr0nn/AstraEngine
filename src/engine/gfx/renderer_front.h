#ifndef RENDERER_FRONT_H
#define RENDERER_FRONT_H

#include "../core/utils.h"
#include "renderer_back.h"

#include "../math/shapes.h"

// Colors Structs and funcs
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

static inline void ast_render_rect(ast_Renderer* renderer, ast_rect rect, ast_color color) {
  ast_fcolor fcolor = ast_convert_fcolor(color); 
  f32 c[4] = {fcolor.r, fcolor.g, fcolor.b, fcolor.a};
  
  glUseProgram(renderer->shader_default);

  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, rect.x, rect.y, 0);
  mat4x4_scale_aniso(model, model, 2*rect.w, 2*rect.h, 1);
  mat4x4_rotate_Z(model, model, DEG2RAD(35.6));
  
  ast_mat4 translation = ast_mat4_translate(rect.x, rect.y, 0);
  ast_mat4 scale       = ast_mat4_scale(rect.w, rect.h, 1);
  ast_mat4 model2      = ast_mat4_multiply(translation, scale);
  ast_mat4 model3      = ast_mat4_transpose(&model2);  
  const f32* model_ptr = ast_mat4_to_array(&model3);

  glUniformMatrix4fv(glGetUniformLocation(renderer->shader_default, "model"), 1, GL_FALSE, &model[0][0]);
  glUniform4fv(glGetUniformLocation(renderer->shader_default, "color"), 1, c); 
 
  glBindVertexArray(renderer->vao_quad);

  glBindTexture(GL_TEXTURE_2D, renderer->texture_color);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

  glBindVertexArray(0); 
}

#endif
