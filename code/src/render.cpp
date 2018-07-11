//
//  render.cpp
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#include <stdio.h>
#include "render.h"

/*
 * Draw spp number of samples per pixel (x,y).
 * Stores the result in output.
 */
void render_kernel(Vec3Df *output, float x, float y, int spp)
{
	int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
	Vec3Df color = Vec3Df(0,0,0);	// final pixel color
	
	// sample multiple times per pixel
	for (int s=0; s < spp; s++)
	{
		// anti-aliasing to be implemented here
		Ray cam = getCamRay(x + 0.5, y + 0.5);
		color += PT::computeRadiance(cam) * 1. / spp;		// regular path tracer
	}
	
	output[i] = color;
}
