#ifndef UTILS_H
#define UTILS_H

// print colors
#define ANSI_RESET    "\x1b[0m"
#define ANSI_RED      "\x1b[31m"
#define ANSI_GREEN    "\x1b[32m"
#define ANSI_YELLOW   "\x1b[33m"
#define ANSI_BLUE     "\x1b[34m"
#define ANSI_MAGENTA  "\x1b[35m"
#define ANSI_CYAN     "\x1b[36m"
#define ANSI_WHITE    "\x1b[37m"

#include <stdio.h>

#define ERROR_EXIT(...) fprintf(stderr, ANSI_RED __VA_ARGS__ ANSI_RESET)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R

#define LOG(S, out) fprintf(out, S); fprintf(out, "\n")
#define FLOG(out, format, ...) fprintf(out, format, __VA_ARGS__); fprintf(out, "\n")

#endif
