#ifndef LINALG_H
#define LINALG_H

#include "../core/types.h"
#include <math.h>
#include <stdio.h>

// Type Definitions ------------------------------------------------------
typedef struct {
  f32 x, y;
} ast_vec2;

typedef struct {
  f32 x, y, z;
} ast_vec3;

typedef struct {
  f32 x, y, z, w;
} ast_vec4;

typedef struct {
  f32 m[3][3];
} ast_mat3;

typedef struct {
  f32 m[4][4];
} ast_mat4;

// Debug functions -------------------------------------------------------
static inline void ast_vec2_print(ast_vec2 v) {
  printf("(%f, %f)\n", v.x, v.y);
}

static inline void ast_vec3_print(ast_vec3 v) {
  printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}

static inline void ast_mat3_print(ast_mat3 mat) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      printf("%f ", mat.m[i][j]);
    }
    printf("\n");
  }
}

static inline void ast_mat4_print(ast_mat4 mat) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("%f ", mat.m[i][j]);
    }
    printf("\n");
  }
}

// Conversion functions for OpenGL ---------------------------------------
static inline const f32 *ast_vec2_opengl(const ast_vec2 *v) {
  return (const f32 *)v;
}

static inline const f32 *ast_vec3_opengl(const ast_vec3 *v) {
  return (const f32 *)v;
}

static inline const f32 *ast_vec4_opengl(const ast_vec4 *v) {
  return (const f32 *)v;
}

static inline const f32 *ast_mat3_opengl(const ast_mat3 *mat) {
  return (const f32 *)mat->m;
}

static inline const f32 *ast_mat4_opengl(const ast_mat4 *mat) {
  return (const f32 *)mat->m;
}

// Vector 2D functions ---------------------------------------------------
static inline ast_vec2 ast_vec2_zero() { return (ast_vec2){0.0f, 0.0f}; }

static inline ast_vec2 ast_vec2_add(ast_vec2 a, ast_vec2 b) {
  return (ast_vec2){a.x + b.x, a.y + b.y};
}

static inline ast_vec2 ast_vec2_sub(ast_vec2 a, ast_vec2 b) {
  return (ast_vec2){a.x - b.x, a.y - b.y};
}

static inline ast_vec2 ast_vec2_scale(ast_vec2 v, f32 s) {
  return (ast_vec2){v.x * s, v.y * s};
}

static inline f32 ast_vec2_dot(ast_vec2 a, ast_vec2 b) {
  return a.x * b.x + a.y * b.y;
}

static inline f32 ast_vec2_length(ast_vec2 v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

static inline ast_vec2 ast_vec2_normalize(ast_vec2 v) {
  f32 len = ast_vec2_length(v);
  return (len > 0) ? ast_vec2_scale(v, 1.0f / len) : (ast_vec2){0.0f, 0.0f};
}

// Vector 3D functions ---------------------------------------------------
static inline ast_vec3 ast_vec3_add(ast_vec3 a, ast_vec3 b) {
  return (ast_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline ast_vec3 ast_vec3_sub(ast_vec3 a, ast_vec3 b) {
  return (ast_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline ast_vec3 ast_vec3_scale(ast_vec3 v, f32 s) {
  return (ast_vec3){v.x * s, v.y * s, v.z * s};
}

static inline f32 ast_vec3_dot(ast_vec3 a, ast_vec3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline ast_vec3 ast_vec3_cross(ast_vec3 a, ast_vec3 b) {
  return (ast_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x};
}

static inline f32 ast_vec3_length(ast_vec3 v) {
  return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline ast_vec3 ast_vec3_normalize(ast_vec3 v) {
  f32 len = ast_vec3_length(v);
  return (len > 0) ? ast_vec3_scale(v, 1.0f / len)
                   : (ast_vec3){0.0f, 0.0f, 0.0f};
}

// Matrix 3x3 functions --------------------------------------------------
static inline ast_mat3 ast_mat3_identity() {
  return (ast_mat3){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
}

static inline ast_mat3 ast_mat3_scale(f32 sx, f32 sy) {
  return (ast_mat3){{{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}}};
}

static inline ast_mat3 ast_mat3_translate(f32 tx, f32 ty) {
  return (ast_mat3){{{1, 0, 0}, {0, 1, 0}, {tx, ty, 1}}};
}

static inline ast_mat3 ast_mat3_rotate(f32 angle) {
  f32 c = cosf(angle);
  f32 s = sinf(angle);
  return (ast_mat3){{{c, s, 0}, {-s, c, 0}, {0, 0, 1}}};
}

static inline ast_mat3 ast_mat3_multiply(ast_mat3 a, ast_mat3 b) {
  ast_mat3 result = {0};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result.m[i][j] =
          a.m[0][j] * b.m[i][0] + a.m[1][j] * b.m[i][1] + a.m[2][j] * b.m[i][2];
    }
  }
  return result;
}

static inline ast_vec2 ast_mat3_transform_vec2(ast_mat3 m, ast_vec2 v) {
  return (ast_vec2){m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0],
                    m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1]};
}

static inline ast_mat3 ast_mat3_compose(ast_mat3 scale, ast_mat3 rotate,
                                        ast_mat3 translate) {
  return ast_mat3_multiply(ast_mat3_multiply(translate, rotate), scale);
}

// Matrix 4x4 functions --------------------------------------------------
static inline ast_mat4 ast_mat4_identity() {
  return (ast_mat4){{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

static inline ast_mat4 ast_mat4_scale(f32 sx, f32 sy, f32 sz) {
  return (ast_mat4){
      {{sx, 0, 0, 0}, {0, sy, 0, 0}, {0, 0, sz, 0}, {0, 0, 0, 1}}};
}

static inline ast_mat4 ast_mat4_translate(f32 tx, f32 ty, f32 tz) {
  return (ast_mat4){
      {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {tx, ty, tz, 1}}};
}

static inline ast_mat4 ast_mat4_rotate_x(f32 angle) {
  f32 c = cosf(angle);
  f32 s = sinf(angle);
  return (ast_mat4){{{1, 0, 0, 0}, {0, c, s, 0}, {0, -s, c, 0}, {0, 0, 0, 1}}};
}

static inline ast_mat4 ast_mat4_rotate_y(f32 angle) {
  f32 c = cosf(angle);
  f32 s = sinf(angle);
  return (ast_mat4){{{c, 0, -s, 0}, {0, 1, 0, 0}, {s, 0, c, 0}, {0, 0, 0, 1}}};
}

static inline ast_mat4 ast_mat4_rotate_z(f32 angle) {
  f32 c = cosf(angle);
  f32 s = sinf(angle);
  return (ast_mat4){{{c, s, 0, 0}, {-s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

static inline ast_mat4 ast_mat4_multiply(ast_mat4 a, ast_mat4 b) {
  ast_mat4 result = {0};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.m[i][j] = a.m[0][j] * b.m[i][0] + a.m[1][j] * b.m[i][1] +
                       a.m[2][j] * b.m[i][2] + a.m[3][j] * b.m[i][3];
    }
  }
  return result;
}

static inline ast_vec3 ast_mat4_transform_vec3(ast_mat4 m, ast_vec3 v) {
  return (ast_vec3){
      m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0],
      m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1],
      m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2]};
}

static inline ast_mat4 ast_mat4_transpose(const ast_mat4 *m) {
  return (ast_mat4){{{m->m[0][0], m->m[1][0], m->m[2][0], m->m[3][0]},
                     {m->m[0][1], m->m[1][1], m->m[2][1], m->m[3][1]},
                     {m->m[0][2], m->m[1][2], m->m[2][2], m->m[3][2]},
                     {m->m[0][3], m->m[1][3], m->m[2][3], m->m[3][3]}}};
}

static inline ast_mat4 ast_mat4_compose(ast_mat4 scale, ast_mat4 rotate,
                                        ast_mat4 translate) {
  return ast_mat4_multiply(ast_mat4_multiply(translate, rotate), scale);
}

static inline ast_mat4 ast_mat4_ortho(f32 left, f32 right, f32 bottom, f32 top,
                                      f32 near, f32 far) {
  // Orthographic projection
  ast_mat4 result = {0};
  result.m[0][0] = 2.0f / (right - left);
  result.m[1][0] = 0.0f;
  result.m[2][0] = 0.0f;
  result.m[3][0] = -(right + left) / (right - left);

  result.m[0][1] = 0.0f;
  result.m[1][1] = 2.0f / (top - bottom);
  result.m[2][1] = 0.0f;
  result.m[3][1] = -(top + bottom) / (top - bottom);

  result.m[0][2] = 0.0f;
  result.m[1][2] = 0.0f;
  result.m[2][2] = -2.0f / (far - near);
  result.m[3][2] = -(far + near) / (far - near);

  result.m[0][3] = 0.0f;
  result.m[1][3] = 0.0f;
  result.m[2][3] = 0.0f;
  result.m[3][3] = 1.0f;

  return result;
}

#endif // LINALG_H
