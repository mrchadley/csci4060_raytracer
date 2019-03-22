CC = g++
DEPS = main.cpp vec3.cpp sphere.cpp raytracer.cpp lodepng/lodepng.cpp
FLAGS = -I. -I./lodepng


raytracer: $(DEPS)
	mkdir -p output
	$(CC) $(DEPS) -o output/raytracer.exe $(FLAGS)