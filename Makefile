# Makefile

APP_SRC := src/main.c\
					 src/callbacks.c\
					 src/core.c\
					 ext/glad/glad.c\

CLFAGS   = -Wall
LDFLAGS  = -lm -lX11 -lpthread -lXrandr -lXi -ldl 

all: linux
	
linux: linux-build linux-run
linux-build:
	@echo "Building Linux executable..."
	gcc $(APP_SRC) $(CLFAGS) $(LDFLAGS) -o builds/linux/app
linux-run:
	@echo "Running Linux executable..."
	./builds/linux/app

web: web-build web-run
web-build:
	@echo "Building Web executable..."
	emcc $(APP_SRC) -DWEB=1 -o index.js -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1
	mv index.js builds/web/index.js
	mv index.wasm builds/web/index.wasm
web-run:
	@echo "Running Web executable..."
	emrun builds/web/index.html
	
