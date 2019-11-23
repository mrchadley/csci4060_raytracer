#include "raytracer.h"
#include "lodepng/lodepng.h"
#include <cstdio>
#include <algorithm>
#include <cmath>

#ifndef M_PI
	#define M_PI 3.141592653589793
#endif
#ifndef INFINITY
	#define INFINITY 1e8
#endif
#define MAX_RAY_DEPTH 5


float Mix(const float &a, const float &b, const float &mix)
{
	return b * mix + a * (1 - mix);
}


Raytracer::Raytracer(int width, int height)
 : width(width), height(height)
{
	
}

void Raytracer::Render(const std::vector<Sphere> spheres)
{
	image = (unsigned char *)malloc(width * height * 4);

	invWidth = 1 / float(width);
	invHeight = 1 / float(height);
	float fov = 45;
	aspectRatio = width / float(height);
	angle = tan(M_PI * 0.5 * fov / 180.0);

	//temp for testing output
	//actual raytracing will be done in the child class render() method
	/*unsigned x, y;
	unsigned index;
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			index = 4 * width * y + 4 * x;
			image[index + 0] = 255 * !(x & y);
    		image[index + 1] = x ^ y;
    		image[index + 2] = x | y;
    		image[index + 3] = 255;
		}
	}*/
}

Vec3f Raytracer::Trace(const Vec3f &origin, const Vec3f &direction, 
				const std::vector<Sphere> spheres, const int &depth)
{
	float tnear = INFINITY;
	const Sphere* sphere = NULL;

	for(unsigned i = 0; i < spheres.size(); i++)
	{
		float t0 = INFINITY, t1 = INFINITY;
		if(spheres[i].Intersect(origin, direction, t0, t1))
		{
			if(t0 < 0) t0 = t1;
			if(t0 < tnear)
			{
				tnear = t0;
				sphere = &spheres[i];
			}
		}
	}

	//no intersection, return black
	if(!sphere) return Vec3f(.2f);

	Vec3f surfaceColour = 0;
	Vec3f hitPoint = origin + direction * tnear;
	Vec3f hitNorm = hitPoint - sphere->center;
	hitNorm.Normalize();

	float bias = 1e-4;
	bool inside = false;

	if(direction.Dot(hitNorm) > 0) hitNorm = -hitNorm, inside = true;
	if((sphere->transparency > 0 || sphere->reflectivity > 0) && depth < MAX_RAY_DEPTH)
	{
		//reflective or transparent spheres
		float facingRatio = -direction.Dot(hitNorm);

		float fresnel = Mix(pow(1 - facingRatio, 3), 1, 0.1f);
		Vec3f reflectDir = direction - hitNorm * 2 * direction.Dot(hitNorm);
		reflectDir.Normalize();

		Vec3f reflection = Trace(hitPoint + hitNorm * bias, reflectDir, spheres, depth + 1);

		Vec3f refraction = 0;

		if(sphere->transparency)
		{
			float ior = 1.1, eta = (inside) ? ior : 1 / ior;
			float cosi = -hitNorm.Dot(direction);
			float k = 1 - eta * eta * (1 - cosi * cosi);
			Vec3f refractDir = direction * eta + hitNorm * (eta * cosi - sqrt(k));
			refractDir.Normalize();
			refraction = Trace(hitPoint - hitNorm * bias, refractDir, spheres, depth + 1);
		}
		surfaceColour = (reflection * fresnel + refraction * (1 - fresnel) * sphere->transparency) * sphere->surfaceColour;
	}
	else
	{
		//diffuse sphere, no more raytracing
		for(unsigned i = 0; i < spheres.size(); i++)
		{
			if(spheres[i].emissionColour.x > 0)
			{
				//this is a light
				Vec3f transmission = 1;
				Vec3f lightDirection = spheres[i].center - hitPoint;
				lightDirection.Normalize();
				for(unsigned j = 0; j < spheres.size(); j++)
				{
					if(i != j)
					{
						float t0, t1;
						if(spheres[j].Intersect(hitPoint + hitNorm * bias, lightDirection, t0, t1))
						{
							transmission = 0;
							break;
						}
					}
				}

				surfaceColour += sphere->surfaceColour * transmission *
					std::max(0.0f, hitNorm.Dot(lightDirection)) * spheres[i].emissionColour;
			}
		}
	}
	
	return surfaceColour + sphere->emissionColour;
}

void Raytracer::WritePNG()
{
	unsigned error = lodepng_encode32_file(filename, image, width, height);

	if(error) printf("Error: WritePNG() %u %s\n", error, lodepng_error_text(error));
}


SequentialRaytracer::SequentialRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "sequential.png";
}

void SequentialRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);

	unsigned x, y;
	unsigned index;

	Vec3f pixel;

	unsigned num_pix = width * height;

	for(index = 0; index < num_pix; index++)
	{
		x = index % width;
		y = index / width;

		float rayX = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectRatio;
		float rayY = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;
		Vec3f rayDir = Vec3f(rayX, rayY, -1);
		rayDir.Normalize();

		pixel = Trace(Vec3f(0), rayDir, spheres, 0);
		unsigned ind4 = index * 4;
		image[ind4 + 0] = (unsigned char)(std::min(1.0f, pixel.x) * 255);
    	image[ind4 + 1] = (unsigned char)(std::min(1.0f, pixel.y) * 255);
    	image[ind4 + 2] = (unsigned char)(std::min(1.0f, pixel.z) * 255);
    	image[ind4 + 3] = 255;

	}


	WritePNG();
}


OpenCLRaytracer::OpenCLRaytracer(int width, int height)
 : Raytracer(width, height)
{
	filename = "opencl.png";
}

void OpenCLRaytracer::Render(const std::vector<Sphere> spheres)
{
	Raytracer::Render(spheres);
}