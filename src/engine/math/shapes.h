#ifndef SHAPES_H
#define SHAPES_H

#include "linalg.h"

typedef struct {
  union {
    struct {
      ast_vec2 p1;
      ast_vec2 p2;
      ast_vec2 p3;
    };
    struct {
      ast_vec2 p[3];
    };
  };
} ast_triangle;

typedef struct {
  union {
    struct {
      ast_vec2 pos;
      ast_vec2 dim;
    };
    struct {
      f32 x, y, w, h;
    };
  };
} ast_rect;

typedef struct {
  union {
    struct {
      ast_vec2 pos;
    };
    struct {
      f32 x, y;
    };
  };
  f32 radius;
} ast_circle;

#endif // !SHAPES_H
