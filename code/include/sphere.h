#ifndef sphere_h
#define sphere_h

#include "Vec3D.h"
#include "material.h"
#include "ray.h"

/*
 * Class for sphere intersection
 */
class Sphere
{
public:
	void sphere_init(float radius, Vec3Df &centre, Material &material);
	
	Material getMaterial() {return mat; }
	float getRadius() { return radius; }
	Vec3Df getCentre() { return centre; }

	float intersectSphere(Ray &ray);
	Vec3Df computeNormal(const Vec3Df &hp);

private:
	float radius;
	Vec3Df centre;
	Material mat;
};

#endif
