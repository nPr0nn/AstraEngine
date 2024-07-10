
#ifndef WEB
#define GLFW_IMPL
#endif

#include "core.h"
#include "engine/utils.h"
#include <stdio.h>

#ifdef WEB
// WebGL Shader source code
const char *vertexShaderSource = "attribute vec3 aPos;\n"
                                 "uniform mat4 model;\n"
                                 "void main() {\n"
                                 "    gl_Position = model * vec4(aPos, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSource =
    "precision mediump float;\n"
    "void main() {\n"
    "    gl_FragColor = vec4(0.0, 0.5, 1.0, 1.0); // Blue color\n"
    "}\n";

#else
// Desktop OpenGL Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout(location = 0) in vec3 aPos;\n"
                                 "uniform mat4 model;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    gl_Position = model * vec4(aPos, 1.0);\n"
                                 "}\n";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(0.0, 0.5, 1.0, 1.0); // Blue color\n"
    "}\n";
#endif

// Compile and link shaders
unsigned int createShaderProgram() {
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  }

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

void engine_start(EngineContext *engine_context) {
  // glfw: initialize and configure
  LOG("GLFW Init", stdout);
  if (!glfwInit()) {
    ERROR_EXIT("Failed to initialize GLFW");
  }
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw: window creation
  float screen_width = 1920 * 0.5f;
  float screen_height = 1080 * 0.5f;
  GLFWwindow *window =
      glfwCreateWindow(screen_width, screen_height, "Steiner View", NULL, NULL);
  if (!window) {
    glfwTerminate();
    ERROR_EXIT("ERROR: Failed to create GLFW window\n");
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    ERROR_EXIT("ERROR: Failed to initialize GLAD");
  }

  // Global
  engine_context->window = window;
  engine_context->curr_time = 0;
  engine_context->delta_time = 0;
  engine_context->prev_time = 0;

  glfwSetWindowUserPointer(window, engine_context);

  // Setup shaders and quad rendering
  unsigned int shaderProgram = createShaderProgram();
  engine_context->shaderProgram = shaderProgram;

  // Vertex positions for the quad
  float vertices[] = {
      -0.5f, 0.5f,  0.0f, // Top-left
      0.5f,  0.5f,  0.0f, // Top-right
      0.5f,  -0.5f, 0.0f, // Bottom-right
      -0.5f, -0.5f, 0.0f  // Bottom-left
  };

  // Indices for the two triangles that form the quad
  unsigned int indices[] = {
      0, 1, 2, // First triangle
      2, 3, 0  // Second triangle
  };

  glGenVertexArrays(1, &engine_context->VAO);
  glGenBuffers(1, &engine_context->VBO);
  glGenBuffers(1, &engine_context->EBO);

  glBindVertexArray(engine_context->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, engine_context->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine_context->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  engine_context->angle = 0.0f;
}

// engine: core loop with update and render
void core_loop(void *args) {
  EngineContext *ctx = (EngineContext *)args;

  // delta time
  ctx->curr_time = glfwGetTime();
  ctx->delta_time = ctx->curr_time - ctx->prev_time;
  ctx->prev_time = ctx->curr_time;
  float dt = ctx->delta_time;

  // inputs
  process_input(ctx->window);

  // background
  glClearColor(1.0f, 0.5f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Use shader program
  glUseProgram(ctx->shaderProgram);

  // Update angle
  ctx->angle += dt;
  f32 angle = ctx->angle;

  // Create rotation matrix
  float model[16] = {
      cos(angle), -sin(angle), 0.0f, 0.0f, sin(angle), cos(angle), 0.0f, 0.0f,
      0.0f,       0.0f,        1.0f, 0.0f, 0.0f,       0.0f,       0.0f, 1.0f};

  unsigned int modelLoc = glGetUniformLocation(ctx->shaderProgram, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

  // Draw quad
  glBindVertexArray(ctx->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glfwSwapBuffers(ctx->window);
  glfwPollEvents();
}

void engine_terminate(EngineContext *engine_context) {
  glDeleteVertexArrays(1, &engine_context->VAO);
  glDeleteBuffers(1, &engine_context->VBO);
  glDeleteBuffers(1, &engine_context->EBO);
  glDeleteProgram(engine_context->shaderProgram);
  glfwTerminate();
}
