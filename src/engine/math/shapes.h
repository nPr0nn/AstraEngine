#ifndef SHAPES_H
#define SHAPES_H

#include "linalg.h"

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
