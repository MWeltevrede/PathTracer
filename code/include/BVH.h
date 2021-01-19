#ifndef BVH_h
#define BVH_h

#include "intersection.h"
#include "ray.h"
#include "sphere.h"
#include "light.h"
#include <vector>

/*
 * Structures
 */
extern std::vector<Sphere> spheres;
extern std::vector<Light *> lights;

/*
 *	Find closest intersection using a BVH structure.
 */
Intersection computeIntersection(Ray &r);

/*
 * Compute whether there is occlusion along the given ray.
 */
bool isOccluded(Ray &r, float distance_to_light);

#endif
