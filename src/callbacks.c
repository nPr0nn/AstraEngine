
#include "core.h"
#include "engine/types.h"

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  // EngineContext* ctx = glfwGetWindowUserPointer(window);
}

// glfw: query to check state of relevants keys
void process_input(GLFWwindow *window) {
  // EngineContext* ctx = glfwGetWindowUserPointer(window);
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
