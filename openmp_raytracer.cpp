#include "raytracer.h"
#include <omp.h>
#include <algorithm>

#define NUM_THREADS 8

OpenMPRaytracer::OpenMPRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "openmp.png";
}

void OpenMPRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("OpenMPRaytracer::Render()\n");

	omp_set_num_threads(NUM_THREADS);

	unsigned num_pix = width * height;
	#pragma omp parallel for
	for(unsigned index = 0; index < num_pix; index++)
	{
		unsigned x = index % width;
		unsigned y = index / width;

		float rayX = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectRatio;
			float rayY = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;
			Vec3f rayDir = Vec3f(rayX, rayY, -1);
			rayDir.Normalize();

			Vec3f pixel = Trace(Vec3f(0), rayDir, spheres, 0);
			unsigned ind4 = index * 4;
			image[ind4 + 0] = (unsigned char)(std::min(1.0f, pixel.x) * 255);
    		image[ind4 + 1] = (unsigned char)(std::min(1.0f, pixel.y) * 255);
    		image[ind4 + 2] = (unsigned char)(std::min(1.0f, pixel.z) * 255);
    		image[ind4 + 3] = 255;

	}

	WritePNG();
}
