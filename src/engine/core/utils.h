#ifndef UTILS_H
#define UTILS_H

//-- External Dependencies ------
// GLFW for window creation
// GLAD for OpenGL calls
#include "../../_ext/glad/glad.h"
#include "../../_ext/glad/glad.c"
#ifndef WEB_BUILD
  #ifndef GLFW_IMPL
    #define GLFW_IMPL
  #endif
#endif
#include "../../_ext/glfw/glfw.h"

#ifdef WEB_BUILD
#include <emscripten.h>
#endif
//------------------------------

// Rename standard types 
#include "types.h"

// Array get size macro
#define ast_array_size(x) (sizeof((x)) / sizeof((x)[0]))

// Bytes to KB, MB, GB
#define KB(x) ((u64) 1024 * x)
#define MB(x) ((u64) 1024 * KB(x))
#define GB(x) ((u64) 1024 * MB(x))

#define PI 3.14159265358979323846
#define DEG2RAD(x) (x * (PI / 180.0f))
#define RAD2DEG(x) (x * (180.0f / PI))

// Useful logging functions
#include "logger.h"

#endif
