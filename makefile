CC = g++
DEPS = main.cpp vec3.cpp sphere.cpp raytracer.cpp openmp_raytracer.cpp pthread_raytracer.cpp lodepng/lodepng.cpp
PREFLAGS = -fopenmp
FLAGS = -pthread -I. -I./lodepng


raytracer: $(DEPS)
	mkdir -p output
	$(CC) $(DEPS) $(PREFLAGS) -o output/raytracer.exe $(FLAGS)