
#include "core.h"
#include "engine/utils.h"
#include <stdio.h>

void engine_start(EngineContext* engine_context)
{
  // glfw: initialize and configure
  LOG("GLFW Init", stdout);  
  glfwInit();
  glfwWindowHint(GLFW_SAMPLES, 4); 
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
  // glfwWindowHint(GLFW_RESIZABLE, 1);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
  
  // glfw: window creation
  f32 screen_width  = 1920 * 0.5f;
  f32 screen_height = 1080 * 0.5f;
  GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "Steiner View", NULL, NULL);
 
  if(window == NULL){
    glfwTerminate();
    ERROR_EXIT("ERROR: Failed to create GLFW window\n");
  }
  
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    ERROR_EXIT("ERROR: Failed to initialize GLAD");
  }    

  // Global
  engine_context->window = window;

  // Delta Time
  engine_context->curr_time  = 0;
  engine_context->delta_time = 0;
  engine_context->prev_time  = 0;
  
  glfwSetWindowUserPointer(window, engine_context); 

  // setup the quad rendering
  
  // Vertex positions for the quad
  f32 vertices[] = {
      // Positions
      -0.5f,  0.5f, 0.0f,  // Top-left
       0.5f,  0.5f, 0.0f,  // Top-right
       0.5f, -0.5f, 0.0f,  // Bottom-right
      -0.5f, -0.5f, 0.0f   // Bottom-left
  };

  // Indices for the two triangles that form the quad
  u32 indices[] = {
      0, 1, 2,  // First triangle
      2, 3, 0   // Second triangle
  };

  glGenVertexArrays(1, &engine_context->VAO);
  glGenBuffers(1, &engine_context->VBO);
  glGenBuffers(1, &engine_context->EBO);

  glBindVertexArray(engine_context->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, engine_context->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine_context->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0); 
}

// engine: core loop with update and render
void core_loop(void* args)
{
  EngineContext* ctx = (EngineContext*) args;
 
  // delta time
  ctx->curr_time  = glfwGetTime();
  ctx->delta_time = ctx->curr_time - ctx->prev_time;
  ctx->prev_time  = ctx->curr_time;
  f32 dt          = ctx->delta_time;
  // FLOG(stdout, "%.9f", dt);
   
  // inputs
  process_input(ctx->window);

  // background 
  glClearColor(1.0f, 0.5f, 0.8f, 1.0f); 
  glClear(GL_COLOR_BUFFER_BIT);

  f32 angle = 0.0f;
  
  // Apply rotation using fixed-function pipeline
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -1.0f); // Move the quad back
  glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

  glBindVertexArray(ctx->VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glPopMatrix();

  glfwSwapBuffers(ctx->window);   
  glfwPollEvents(); 
}

void engine_terminate(EngineContext* engine_context){
  glfwTerminate();
}

