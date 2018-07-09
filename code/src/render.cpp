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
void render_kernel(Vec3Df *output, int x, int y, int spp)
{
	int i = (getHeight() - 1 - y) * getWidth() + x;	// row-major index, (0,0) in bottom left
	Vec3Df color = Vec3Df(0,0,0);	// final pixel color
	
	// sample multiple times per pixel
	for (int s=0; s < spp; s++)
	{
		// anti-aliasing to be implemented here
		Ray cam = getCamRay(x + 0.5, y + 0.5);
		color += PT::computeRadiance(cam) / spp;		// regular path tracer
	}
	
	output[i] = color;
}
