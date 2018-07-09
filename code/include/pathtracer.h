//
//  pathtracer.h
//  
//
//  Created by Max Weltevrede on 08/07/2018.
//

#ifndef pathtracer_h
#define pathtracer_h

#include "ray.h"
#include "BVH.h"
#include "intersection.h"

/*
 * Path tracer.
 */
namespace PT
{
	Vec3Df computeRadiance(Ray &r);
}

#endif
