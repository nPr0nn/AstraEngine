#ifndef ASTRA_H
#define ASTRA_H

#include "core/utils.h"
#include "core/window.h"

#include "gfx/renderer_front.h"

#include "math/linalg.h"
#include "math/shapes.h"

static inline void ast_begin_render(ast_Window* window, ast_Renderer* renderer) {
  glfwMakeContextCurrent(window);
  glClear(GL_COLOR_BUFFER_BIT);  
}

static inline void ast_blit_background(ast_color color){
  ast_fcolor c = ast_convert_fcolor(color);
  glClearColor(c.r, c.g, c.b, c.a); 
}

static inline void ast_end_render(ast_Window* window, ast_Renderer* renderer) { 
  // Swap buffers
  glfwSwapBuffers(window);
  glfwPollEvents(); 
}

#endif // !ASTRA_H
