#include "raytracer.h"
#include <pthread.h>
#include <algorithm>

struct RayData
{
	int thread_num;
	PThreadRaytracer *ptr;
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

	
	pthread_t threads[NUM_THREADS];// = (pthread_t *)malloc(num_pix * sizeof(pthread_t)); //will probably actually have to malloc this
	struct RayData data[NUM_THREADS];// = (RayData *)malloc(num_pix * sizeof(RayData));
	pthread_attr_t attr;
	void *status;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(int index = 0; index < NUM_THREADS; index++)
	{
		data[index].thread_num = index;
		data[index].ptr = this;
		data[index].spheres = spheres;


		int error = pthread_create(&threads[index], &attr, RayWrapper, (void *)&data[index]);

		if(error)
		{
			printf("ERROR: create()\n");
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);

	for(int i = 0; i < NUM_THREADS; i++)
	{
		int error = pthread_join(threads[i], &status);
		if(error)
		{
			printf("ERROR: join()\n");
		}
	}

	WritePNG();
}


void PThreadRaytracer::PrimaryRayRoutine(int thread_num, std::vector<Sphere> spheres)
{
	//struct RayData *data = (RayData *)arg;

	//printf("PThreadRaytracer::PrimaryRayRoutine()\n");
	unsigned num_pix = width * height;
	
	for(unsigned index = thread_num; index < num_pix; index += NUM_THREADS)
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

	pthread_exit(0);
}

void * PThreadRaytracer::RayWrapper(void *arg)
{

	struct RayData *data = (RayData *)arg;

	data->ptr->PrimaryRayRoutine(data->thread_num, data->spheres);
}