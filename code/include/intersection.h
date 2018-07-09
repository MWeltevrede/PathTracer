//
//  intersection.h
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#ifndef intersection_h
#define intersection_h

#include "material.h"

/*
 * The type of intersection.
 */
enum Intersect_type { TRIANGLE, SPHERE };

/*
 * Intersection structure
 */
struct Intersection
{
	bool hit = false;
	Intersect_type type = SPHERE;
	Material material;	// material of intersected object
	Vec3Df normal(0,0,0);
	Vec3Df hp(0,0,0);		// intersection/hit point
	
};

#endif /* intersection_h */
