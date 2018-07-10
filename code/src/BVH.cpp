//
//  BVH.cpp
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#include "BVH.h"
#include <cfloat>
#include <math.h>

#define epsilon 1.e-6

/*
 * Doesn't have a BVH yet.
 */
Intersection computeIntersection(Ray &r)
{
	// intersect with all the spheres
	float t = FLT_MAX;
	Intersection inter;
	for (Sphere s : spheres)
	{
		float temp = s.intersectSphere(r);
		if (temp < t)
		{
			inter.hit = true;
			inter.type = SPHERE;
			inter.material = s.getMaterial();
			inter.hp = r.origin + temp * r.dir;
			inter.normal = s.computeNormal(inter.hp);
			t = temp;
		}
	}
	return inter;
}

/*
 * Computer whether the given ray is occluded
 */
bool isOccluded(Ray &r, float distance_to_light)
{
	bool result = false;
	Intersection inter = computeIntersection(r);
	
	// compute distance from origin to hp and light.
	float distance_to_hp_sq = Vec3Df::dotProduct(inter.hp - r.origin, inter.hp - r.origin);
	
	if (distance_to_hp_sq > epsilon*epsilon && distance_to_hp_sq < pow(distance_to_light - epsilon, 2))
	{
		result = true;
	}
	
	return result;
}
