#include <iostream>

#ifndef VEC3_H
#define VEC3_H

class Vec3f
{
public:
	float x, y, z;

	Vec3f();
	Vec3f(float a);
	Vec3f(float x, float y, float z);


	Vec3f operator+(const Vec3f &v) const;
	Vec3f operator-(const Vec3f &v) const;
	Vec3f operator*(const Vec3f &v) const;
	Vec3f operator*(const float &f) const;

	Vec3f operator-() const;

	friend std::ostream &operator<<(std::ostream &os, const Vec3f v);
};

#endif //VEC3_H