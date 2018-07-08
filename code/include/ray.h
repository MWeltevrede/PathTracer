#ifndef ray_h
#define ray_h

#include "Vec3D.h"

struct Ray
{
	Vec3Df origin;
	Vec3Df dir;
	Ray() {}
	Ray(Vec3Df o_, Vec3Df d_) : origin(o_), dir(d_) {}
};

#endif
