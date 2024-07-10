@echo off
setlocal

REM Define source files
set "SRC_FILES=src/main.c src/callbacks.c src/core.c ext/glad/glad.c"

REM Define common flags
set "COMMON_FLAGS=-Wall"

REM Define Windows-specific flags
set "WIN_FLAGS=-lmingw32 -lgdi32 -lm -luser32 -lkernel32 -lopengl32"

REM Define WebAssembly-specific flags
set "WEB_FLAGS=-DWEB=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1"

if "%1"=="" (
    echo Building Windows executable...
    gcc %SRC_FILES% %COMMON_FLAGS% %WIN_FLAGS% -o out.exe
    echo Running the executable...
    out.exe
) else if "%1"=="web" (
    echo Building WebAssembly executable...
    ext\emsdk\upstream\emscripten\emcc %SRC_FILES% %WEB_FLAGS% -o index.js

    echo WebAssembly build complete.
    mv index.js builds/web/index.js
    mv index.wasm builds/web/index.wasm
    ext\emsdk\upstream\emscripten\emrun builds/web/index.html
)

endlocal
