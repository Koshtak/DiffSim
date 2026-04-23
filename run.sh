#!/bin/bash

TARGET="DiffSim"
SRC_DIR="./src"
LIB_DIR="./lib"
INC_DIR="./include"

echo "DERLENIYOR"


gcc -g -O0 $SRC_DIR/*.c -o $TARGET \
	-I$INC_DIR \
	./lib/libraylib.a \
	-lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
	echo "BASARIYLA DERLENDI"
	echo "BASLATILIYOR"

	export MESA_LOADER_DRIVER_OVERRIDE=crocus
	export MESA_GL_VERSION_OVERRIDE=2.1
	export GLFW_PLATFORM=x11

	./$TARGET
else
	echo "BASARISIZ DERLEME!!!"
fi

