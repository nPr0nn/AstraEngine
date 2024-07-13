
#include "engine/astra.h"

typedef struct GameContext {
  astra_rect rect1 = (astr_rect) {0, 0, 100, 100};
  astra_color c;

  t_rect rect = (astra_rect) {0, 0, 100, 100};

  astra_vec2 v       = vec2_add(v1, v2);
  astra_circle circ;
  
  vec2 
  rect 
  circle 

  // void (*game_init)(void *);
} GameContext;

void init(void *args) {

}

void update(void *args) {

}

void render(void *args) {

}

void terminate(void *args) {

}

int main() {
  EngineContext engine_context;
  astra_engine_init(&engine_context);
  
  GameContext game_context{
    .game_init      = init,
    .game_update    = update,
    .game_render    = render,
    .game_terminate = terminate
  };
  engine_context.game_context = &game_context;
  
  astra_engine_run(&engine_context);
  astra_engine_terminate(&engine_context);
  return 0;
}
