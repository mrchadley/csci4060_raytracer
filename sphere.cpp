#include "sphere.h"
#include <cmath>

Sphere::Sphere(const Vec3f &center, const float &radius, const Vec3f &surfaceCol, const float &trans, const float &refl, const Vec3f &emissionCol)
 : center(center), radius(radius), radiusSqr(radius * radius), surfaceColour(surfaceCol), emissionColour(emissionCol), transparency(trans), reflectivity(refl)
{

}

bool Sphere::Intersect(const Vec3f &castPoint, const Vec3f &castDir, float &t0, float &t1) const
{
	Vec3f ec = center - castPoint;
	float tca = ec.Dot(castDir);

	if(tca < 0) return false;

	float dSqr = ec.Dot(ec) - tca * tca;

	if(dSqr > radiusSqr) return false;

	float thc = sqrt(radiusSqr - dSqr);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}


std::ostream &operator<<(std::ostream &os, const Sphere s)
{
	os << "sphere:[center" << s.center << ", radius(" << s.radius << "), trans(" << s.transparency << "), refl(" << s.reflectivity << ")," << "\n"
		<< "\tcolour" << s.surfaceColour <<", emission" << s.emissionColour << "]";
	return os;
}