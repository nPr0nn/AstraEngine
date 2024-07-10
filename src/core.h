#ifndef CORE_H
#define CORE_H

#include "engine/engine_context.h"

// glfw
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void engine_start(EngineContext *engine_context);
void engine_terminate(EngineContext *engine_context);

// core engine
void process_input(GLFWwindow *window);
void core_loop(void *engine_context);

#endif
