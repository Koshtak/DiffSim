# DiffSim
A simulation made with raylib in C language. Main goal of this project is to simulate real life physics for objects to interact with.
(legacy hardware optimized)

#TECHNICAL PROPERTIES
incompatibility between graphic API and legacy hardware has been solved with:
>static linking
>OpenGL support(GRAPHICS_API_OPENGL_21)
>to prevent Xwayland segfaults X11 backend and crocus has been forced



#SETUP
#make sure you have 'mesa', 'libx11', and 'gcc' installed

bash>
chmod +x run.sh
./run.sh
