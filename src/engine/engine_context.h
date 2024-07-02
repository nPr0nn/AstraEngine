#ifndef CONTEXT_H
#define CONTEXT_H

#include "../../ext/glad/glad.h"
#include "../../ext/glfw/zig-out/include/GLFW/glfw3.h"

#include "types.h" 
#include "utils.h"

typedef struct EngineContext {
  // EngineContext Lifetime
  bool start_context;
  bool end_context;
 
  // Glfw 
  GLFWwindow* window;
    
  // Delta Time
  f32 curr_time;
  f32 prev_time;
  f32 delta_time;

  f32 angle; 
  
  // quad
  u32 VAO, VBO, EBO;
  u32 shaderProgram;

} EngineContext;

#endif

