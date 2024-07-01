
#include "core.h"

typedef void (*main_loop_ptr)(void *);
#ifdef WEB
#include <emscripten.h>
void engine_run(void *ctx, main_loop_ptr core_loop) {
  emscripten_set_main_loop_arg(core_loop, ctx, -1, 1);
}
#else
void engine_run(void *ctx, main_loop_ptr core_loop) {
  EngineContext *engine_context = (EngineContext *)ctx;
  while (!glfwWindowShouldClose(engine_context->window)) {
    core_loop(ctx);
  }
}
#endif

int main() {
  EngineContext engine_context;
  engine_start(&engine_context);
  engine_run(&engine_context, core_loop);
  engine_terminate(&engine_context);
  return 0;
}
