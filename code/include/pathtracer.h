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
#include "random.h"
#include <random>

// Uniform random number generator [0, 1)
extern std::mt19937 gen;	// Mersenne twister seeded with rd
extern std::uniform_real_distribution<double> dis;

/*
 * Path tracer.
 */
namespace PT
{
	Vec3Df computeRadiance(Ray &r, std::vector<Halton> &halt);
}

#endif
