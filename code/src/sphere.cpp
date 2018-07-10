#include "sphere.h"
#include <cfloat>

#define epsilon 1e-4

void Sphere::sphere_init(float r, Vec3Df &c, Material &m)
{
	radius = r;
	centre = c;
	mat = m;
}

float Sphere::intersectSphere(Ray &r)
{
	float t = FLT_MAX;
	float t1, t2;
	Vec3Df dir = r.dir;

	float a = Vec3Df::dotProduct(dir, dir);
	float b = 2. * Vec3Df::dotProduct(dir, r.origin - centre);
	float c = Vec3Df::dotProduct(r.origin - centre, r.origin - centre) - radius*radius;

	// abc formula
	float discr = b * b - 4 * a * c;
	if (discr < 0) return t;
	if (discr == 0)
	{
		t1 = t2 = -0.5*b / a;
	}
	else {
		float q = (b > 0) ? -0.5*(b + sqrt(discr)) : -0.5*(b - sqrt(discr));
		t1 = q / a;
		t2 = c / q;
	}

	if (t1 > t2) std::swap(t1, t2);

	// avoid self intersection
	if (t1 < epsilon) t1 = -1;
	if (t2 < epsilon) t2 = -1;

	if (t1 < 0 && t2 < 0) return t;

	t = t1;
	if (t1 < 0) t = t2;	
	if (t2 < 0) t = t1;

	return t;
}

Vec3Df Sphere::computeNormal(const Vec3Df &hp)
{
	Vec3Df n = hp - centre;
	n.normalize();
	return n;
}
