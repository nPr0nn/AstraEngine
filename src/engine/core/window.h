#ifndef WINDOW_H
#define WINDOW_H

#include "logger.h"
#include "utils.h"

// Window Callbacks ---------------------------------------------
// glfw: whenever the window size changed (by OS or user resize) this callback executes
static inline void framebuffer_resize_callback(GLFWwindow *window, i32 width, i32 height) {
  glViewport(0, 0, width, height);
}

// glfw: whenever a key is pressed, this callback executes
static inline void keyboard_input_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods){
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
// ----------------------------------------------------------------

typedef GLFWwindow ast_Window;

static inline ast_Window* ast_init_window(char* title, i32 screen_width, i32 screen_height) {
   // glfw: initialize and configure  
  LOG_INFO("Initializing 'Astra Framework' 0.1\n");

  if (!glfwInit()) {
    LOG_ERROR("Failed to initialize GLFW\n");
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  ast_Window* window = glfwCreateWindow(screen_width, screen_height, title, NULL, NULL); 
  if (!window) {
    glfwTerminate();
    LOG_ERROR("Failed to create GLFW window\n");
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
  glfwSetKeyCallback(window, keyboard_input_callback);

  // glad: Load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    LOG_ERROR("Failed to initialize GLAD\n");
  }
  LOG_INFO("GLFW: %s\n", glfwGetVersionString());
  LOG_INFO("GLAD: OpenGL context successfully initialized\n"); 
  LOG_INFO("GL:   OpenGL device information:\n");
  LOG_INFO("      - Vendor:    %s\n", glGetString(GL_VENDOR));
  LOG_INFO("      - Renderer:  %s\n", glGetString(GL_RENDERER)); 
  LOG_INFO("      - Version:   %s\n", glGetString(GL_VERSION));
  
  glViewport(0, 0, screen_width, screen_height); 
  return window;
}

static inline void ast_get_window_size(ast_Window* window, i32* width, i32* height) {
  glfwGetFramebufferSize(window, width, height);
  return;
}

static inline bool ast_window_should_close(ast_Window* window) {
  return glfwWindowShouldClose(window);
}

static inline void ast_terminate_window(ast_Window* window) {
  glfwTerminate(); 
}

#endif 
