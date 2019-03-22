#include "vec3.h"


Vec3f::Vec3f()
:x(0), y(0), z(0)
{ }
Vec3f::Vec3f(float a)
:x(a), y(a), z(a)
{ }
Vec3f::Vec3f(float x, float y, float z)
:x(x), y(y), z(z)
{ }

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

Vec3f Vec3f::operator-() const
{
	return Vec3f(-x, -y, -z);
}

std::ostream &operator<<(std::ostream &os, const Vec3f v)
{
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}