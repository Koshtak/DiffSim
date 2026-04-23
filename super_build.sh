#!/bin/bash

if [ ! -d "raylib_src" ]; then
	git clone --depth 1 https://github.com/raysan5/raylib.git raylib_src
fi

cd raylib_src/src
make clean
make PLATFORM=PLATFORM_DESKTOP GRAPHICS=GRAPHICS_API_OPENGL_21 RAYLIB_LIBTYPE=STATIC -J$(nproc)
cd ../..

gcc -g -O0 *.c -o app \
	./raylib_src/src/libraylib.a \
	-I./raylib_src/src \
	-lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
	echo "BASARIYLA DERLENDI"

	export MESA_LOADER_DRIVER_OVERRIDE=crocus
	export MESA_GL_VERSION_OVERRIDE=2.1
	export GLFW_PLATFORM_x11
	./app
else
	echo "DERLENMEDI"
fi
