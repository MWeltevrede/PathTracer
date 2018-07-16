//
//  render.cpp
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#include <stdio.h>
#include <vector>
#include "render.h"
#include "random.h"

#define HALT_OFF 1

/*
 * Draw spp number of samples per pixel (x,y).
 * Stores the result in output.
 */
void render_kernel(Vec3Df *output, float x, float y, int spp)
{
	// Uniform random number generator [0, 1)
	std::random_device rd;	// seed
	std::mt19937 gen(rd());	// Mersenne twister seeded with rd
	std::uniform_int_distribution<int> dis(0, UINT_MAX);
	
	// Halton sequence
	std::vector<Halton> halt;
	Halton halt_hem1(7, HALT_OFF);
	halt.push_back(halt_hem1);
	
	Halton halt_hem2(11, HALT_OFF);
	halt.push_back(halt_hem2);
	
	Halton halt_lightsamp1(5, HALT_OFF);
	halt.push_back(halt_lightsamp1);
	
	Halton halt_lightsamp2(7, HALT_OFF);
	halt.push_back(halt_lightsamp2);
	
	Halton halt_light(11, HALT_OFF);
	halt.push_back(halt_light);
	
	int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
	Vec3Df color = Vec3Df(0,0,0);	// final pixel color
	
	// sample multiple times per pixel
	for (int s=0; s < spp; s++)
	{
		// anti-aliasing to be implemented here
		Ray cam = getCamRay(x + 0.5, y + 0.5);
		color += PT::computeRadiance(cam, halt) * 1. / spp;		// regular path tracer
	}
	
	output[i] = color;
}
