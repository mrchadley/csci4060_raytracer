#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

#include "vec3.h"
#include "sphere.h"
#include "raytracer.h"


// raytracer.exe method width height
//		method = [sequential | openmp | pthread | opencl]
int main(int argc, char **argv)
{
	int width = 800, height = 600;
	Raytracer *raytracer;

	if(argc < 4)
	{
		std::cout << "Error: incorrect number of arguments: " << argc << '\n' 
				<< "Usage: raytracer method width height\n\tmethod = [sequential | openmp | pthread | opencl]\n";
		exit(-1);
	}

	char *m = argv[1];
	width = atoi(argv[2]);
	height = atoi(argv[3]);

	if(strcmp(m, "sequential") == 0)
		raytracer = new SequentialRaytracer(width, height);
	else if(strcmp(m, "openmp") == 0)
		raytracer = new OpenMPRaytracer(width, height);
	else if(strcmp(m, "pthread") == 0)
		raytracer = new PThreadRaytracer(width, height);
	else if(strcmp(m, "opencl") == 0)
		raytracer = new OpenCLRaytracer(width, height);
	else
	{
		std::cout << "Error: method not found: " << m << '\n' 
				<< "Usage: raytracer method width=800 height=600\n\tmethod = [sequential | openmp | pthread | opencl]\n";
		exit(-1);
	}


	std::vector<Sphere> spheres;
	// create a bunch of spheres
	// and a light(also a sphere)


	raytracer->Render(spheres);
	raytracer->WritePNG();
	return 0;
}