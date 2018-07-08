//
//  pathtracer.h
//  
//
//  Created by Max Weltevrede on 08/07/2018.
//

#ifndef pathtracer_h
#define pathtracer_h

#include "Ray.h"

namespace PT
{
	Vec3Df computeRadiance(Ray &r);
}

#endif /* pathtracer_h */
