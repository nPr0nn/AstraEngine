
#include "../engine/astra.h"
#include <stdio.h>

typedef struct GameContext {
  ast_Window *window;
  ast_Renderer *renderer;

  ast_rect rect;
} GameContext;

void game_init(GameContext *game_ctx) {
  game_ctx->window   = ast_init_window("Astra Engine", 800, 600);
  game_ctx->renderer = ast_init_renderer(game_ctx->window);
  game_ctx->rect = (ast_rect){.pos = {400, 300}, .dim = {100, 100}};
  return;
}

void game_update(GameContext *game_ctx) { return; }

void game_render(GameContext *game_ctx) {
  // Blit background color to screen
  ast_begin_render(game_ctx->window, game_ctx->renderer);
  
  ast_blit_background((ast_color){240, 150, 255, 255});
  
  ast_color rectColor = (ast_color){255, 255, 255, 255};
  game_ctx->rect.pos.x += 0.1;
  ast_render_rect(game_ctx->renderer, game_ctx->rect, rectColor);

  ast_end_render(game_ctx->window, game_ctx->renderer);
  return;
}

void game_terminate(GameContext *game_ctx) {
  ast_terminate_window(game_ctx->window);
  return;
}

//----------------------------------------------------------------------------

void game_loop(void *context) {
  GameContext *game_ctx = (GameContext *)context;
  game_update(game_ctx);
  game_render(game_ctx);
}

//----------------------------------------------------------------------------

int main() {
  GameContext game_ctx;
  game_init(&game_ctx);

  // if we are building for web, use emscripten main loop
  #ifdef WEB_BUILD
    emscripten_set_main_loop_arg(game_loop, (void *)&game_ctx, -1, 1);
  #else
  // else, use glfw main loop
    while (!ast_window_should_close(game_ctx.window)) {
      game_loop(&game_ctx);
    }
  #endif

  game_terminate(&game_ctx);
  return 0;
}
