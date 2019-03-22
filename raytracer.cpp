#include "raytracer.h"
#include "lodepng/lodepng.h"
#include <stdio.h>

Raytracer::Raytracer(int width, int height)
 : width(width), height(height)
{
	
}

void Raytracer::Render(const std::vector<Sphere> spheres)
{
	printf("Raytracer::Render()\n");

	image = (unsigned char *)malloc(width * height * 4);

	//temp for testing output
	//actual raytracing will be done in the child class render() method
	unsigned x, y;
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
    		image[4 * width * y + 4 * x + 1] = x ^ y;
    		image[4 * width * y + 4 * x + 2] = x | y;
    		image[4 * width * y + 4 * x + 3] = 255;
		}
	}
}

void Raytracer::WritePNG()
{
	unsigned error = lodepng_encode32_file(filename, image, width, height);

	if(error) printf("Error: WritePNG() %u %s\n", error, lodepng_error_text(error));
}


SequentialRaytracer::SequentialRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "output/sequential.png";
}

void SequentialRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("SequentialRaytracer::Render()\n");
}



OpenMPRaytracer::OpenMPRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "output/openmp.png";
}

void OpenMPRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("OpenMPRaytracer::Render()\n");
}



PThreadRaytracer::PThreadRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "output/pthread.png";
}

void PThreadRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("PThreadRaytracer::Render()\n");
}



OpenCLRaytracer::OpenCLRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "output/opencl.png";
}

void OpenCLRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("OpenCLRaytracer::Render()\n");
}