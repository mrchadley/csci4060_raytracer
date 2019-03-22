#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"

class Sphere
{
public:
	Vec3f center;
	float radius, radiusSqr;
	Vec3f surfaceColour;
	Vec3f emissionColour;
	float transparency;
	float reflectivity;

	Sphere(const Vec3f &center, const float &radius, const Vec3f &surfaceCol, const float &trans = 0, const float &refl = 0, const Vec3f &emissionCol = 0);


	bool Intersect(const Vec3f &castPoint, const Vec3f &castDir, float &t0, float &t1) const;


	friend std::ostream &operator<<(std::ostream &os, const Sphere s);
};

#endif //SPHERE_H