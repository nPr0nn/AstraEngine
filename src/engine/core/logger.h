#ifndef LOGGER_H
#define LOGGER_H

// Platform Agnostic Debug Break
#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define EXPORT_FN __declspec(dllexport)
#elif __linux__
#define DEBUG_BREAK() __builtin_trap()
#define EXPORT_FN
#elif __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#define EXPORT_FN
#endif

#include <stdio.h>

// Terminal Debug Color
#define ANSI_RESET    "\x1b[0m"
#define ANSI_RED      "\x1b[31m"
#define ANSI_BLUE     "\x1b[94m"
#define ANSI_YELLOW   "\x1b[93m"

// Logging Macros
#define LOG(out, S) fprintf(out, "%s", S)
#define LOGF(out, format, ...) fprintf(out, format, ##__VA_ARGS__)
#define COLOR_LOG(out, S, color) fprintf(out, "%s%s%s", color, S, ANSI_RESET)

// Trace info
#define LOG_INFO(S, ...) do { COLOR_LOG(stdout, "[INFO] ", ANSI_BLUE); LOGF(stdout, S, ##__VA_ARGS__); } while(0)

// Warning
#define LOG_WARN(S, ...) do { COLOR_LOG(stderr, "[WARNING] ", ANSI_YELLOW); LOGF(stderr, S, ##__VA_ARGS__); } while(0)

// Error
#define LOG_ERROR(S, ...) do { COLOR_LOG(stderr, "[ERROR] ", ANSI_RED); LOGF(stderr, S, ##__VA_ARGS__); } while(0)
#define LOG_ERROR_EXIT(S, ...) do { LOG_ERROR(S, ##__VA_ARGS__); exit(1); } while(0)
#define LOG_ERROR_RETURN(R, S, ...) do { LOG_ERROR(S, ##__VA_ARGS__); return R; } while(0)


// Assert
// #define LOG_ASSERT(C, ...) if (!(C)) { LOG_ERROR("Assert failed: " __VA_ARGS__); DEBUG_BREAK(); }

#endif
