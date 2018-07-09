//
//  BVH.h
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#ifndef BVH_h
#define BVH_h

#include "intersection.h"
#include "ray.h"

/*
 *	Find closest intersection using a BVH structure.
 */
Intersection computeIntersection(Ray &r);

/*
 * Compute whether there is occlusion along the given ray.
 */
bool computeOcclusion(Ray &r);

#endif
