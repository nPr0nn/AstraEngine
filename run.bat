echo "Windows"
gcc src/main.c src/callbacks.c src/core.c ext/glad/glad.c -Wall -lmingw32 -lgdi32 -lm -luser32 -lkernel32 -lopengl32 -o out.exe
