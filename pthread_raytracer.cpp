#include "raytracer.h"
#include <pthread.h>
#include <algorithm>

struct RayData
{
	unsigned index;
	unsigned width;
	float invWidth, invHeight;
	float aspectRatio, angle;
	std::vector<Sphere> spheres;
};




PThreadRaytracer::PThreadRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "pthread.png";
}

void PThreadRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
	printf("PThreadRaytracer::Render()\n");

	unsigned num_pix = width * height;
	pthread_t threads[num_pix]; //will probably actually have to malloc this
	struct RayData data[num_pix];
	pthread_attr_t attr;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(unsigned index = 0; index < num_pix; index++)
	{
		data[index].index = index;
		data[index].width = width;
		data[index].invWidth = invWidth;
		data[index].invHeight = invHeight;
		data[index].aspectRatio = aspectRatio;
		data[index].angle = angle;
		data[index].spheres = spheres;

		int error = pthread_create(&threads[index], &attr, PrimaryRayRoutine, (void *)&data[index]);

		if(error)
		{
			printf("ERROR: create()\n");
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);

	for(unsigned i = 0; i < num_pix; i++)
	{
		int error = pthread_join(threads[i], &status);
		if(error)
		{
			printf("ERROR: join()\n");
		}
	}

	WritePNG();
}


void * PThreadRaytracer::PrimaryRayRoutine(void * arg)
{
	struct RayData *data = (RayData *)arg;

	unsigned x = data->index % data->width;
	unsigned y = data->index / data->width;

	float rayX = (2 * ((x + 0.5f) * data->invWidth) - 1) * data->angle * data->aspectRatio;
	float rayY = (1 - 2 * ((y + 0.5f) * data->invHeight)) * data->angle;
	Vec3f rayDir = Vec3f(rayX, rayY, -1);
	rayDir.Normalize();

	Vec3f pixel = Trace(Vec3f(0), rayDir, data->spheres, 0);
	unsigned ind4 = data->index * 4;
	image[ind4 + 0] = (unsigned char)(std::min(1.0f, pixel.x) * 255);
    image[ind4 + 1] = (unsigned char)(std::min(1.0f, pixel.y) * 255);
    image[ind4 + 2] = (unsigned char)(std::min(1.0f, pixel.z) * 255);
    image[ind4 + 3] = 255;

	pthread_exit(0);
}