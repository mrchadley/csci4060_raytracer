#include "vec3.h"
#include <cmath>

Vec3f::Vec3f()
:x(0), y(0), z(0)
{ }
Vec3f::Vec3f(float a)
:x(a), y(a), z(a)
{ }
Vec3f::Vec3f(float x, float y, float z)
:x(x), y(y), z(z)
{ }

Vec3f &Vec3f::Normalize()
{
	float normSqr = LengthSqr();
	if(normSqr > 0)
	{
		float invNorm = 1 / sqrt(normSqr);
		x *= invNorm, y *= invNorm, z *= invNorm;
	}
	return *this;
}
float Vec3f::LengthSqr()
{
	return x * x + y * y + z * z;
}
float Vec3f::Length()
{
	return sqrt(LengthSqr());
}
float Vec3f::Dot(const Vec3f &v) const
{
	return x * v.x + y * v.y + z * v.z;
}


Vec3f Vec3f::operator+(const Vec3f &v) const
{
	return Vec3f(x + v.x, y + v.y, z + v.z);
}
Vec3f Vec3f::operator-(const Vec3f &v) const
{
	return Vec3f(x - v.x, y - v.y, z - v.z);
}
Vec3f Vec3f::operator*(const Vec3f &v) const
{
	return Vec3f(x * v.x, y * v.y, z * v.z);
}
Vec3f Vec3f::operator*(const float &f) const
{
	return Vec3f(x * f, y * f, z * f);
}

Vec3f &Vec3f::operator+=(const Vec3f &v)
{
	x += v.x, y += v.y, z += v.z;
	return *this;
}


Vec3f Vec3f::operator-() const
{
	return Vec3f(-x, -y, -z);
}




std::ostream &operator<<(std::ostream &os, const Vec3f v)
{
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}