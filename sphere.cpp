#include "sphere.h"

Sphere::Sphere(const Vec3f &center, const float &radius, const Vec3f &surfaceCol, const Vec3f &emissionCol, const float &trans, const float &refl)
 : center(center), radius(radius), surfaceColour(surfaceCol), emissionColour(emissionCol), transparency(trans), reflectivity(refl)
{

}


std::ostream &operator<<(std::ostream &os, const Sphere s)
{
	os << "sphere:[center" << s.center << ", radius(" << s.radius << "), trans(" << s.transparency << "), refl(" << s.reflectivity << ")," << "\n"
		<< "\tcolour" << s.surfaceColour <<", emission" << s.emissionColour << "]";
	return os;
}