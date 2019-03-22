#ifndef TRACER_H
#define TRACER_H

#include <vector>
#include "sphere.h"

class Raytracer
{
public:
	Raytracer(int width, int height);

	//handle the image allocation and file saving
	//call appropriate render method
	virtual void Render(const std::vector<Sphere> spheres);

	void WritePNG();

protected:
	unsigned char *image;
	unsigned int width, height;
	const char *filename;
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