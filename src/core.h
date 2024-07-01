#ifndef CORE_H
#define CORE_H

#include "engine/engine_context.h"

// glfw
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
// void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void engine_start(EngineContext* engine_context);
void engine_terminate(EngineContext* engine_context);

// core engine
void process_input(GLFWwindow* window);
void core_loop(void* engine_context);

#endif
