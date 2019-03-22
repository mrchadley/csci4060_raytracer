#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include "sphere.h"

float Mix(const float &a, const float &b, const float &mix);

class Raytracer
{
public:
	Raytracer(int width, int height);

	//handle the image allocation and file saving
	//call appropriate render method
	virtual void Render(const std::vector<Sphere> spheres);
	Vec3f Trace(const Vec3f &origin, const Vec3f &direction, 
				const std::vector<Sphere> spheres, const int &depth);

	void WritePNG();

protected:
	const char *filename;
	unsigned char *image;

	unsigned int width, height;
	float invWidth, invHeight;
	float aspectRatio, angle;
};

class SequentialRaytracer : public Raytracer
{
public:
	SequentialRaytracer(int width, int height);
	void Render(const std::vector<Sphere> spheres) override;
};

class OpenMPRaytracer : public Raytracer
{
public:
	OpenMPRaytracer(int width, int height);
	void Render(const std::vector<Sphere> spheres) override;
};

class PThreadRaytracer : public Raytracer
{
public:
	PThreadRaytracer(int width, int height);
	void Render(const std::vector<Sphere> spheres) override;
};

class OpenCLRaytracer : public Raytracer
{
public:
	OpenCLRaytracer(int width, int height);
	void Render(const std::vector<Sphere> spheres) override;
};

#endif //TRACER_H