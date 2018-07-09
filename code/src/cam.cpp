//
//  cam.cpp
//  
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
//  Created by Max Weltevrede on 08/07/2018.
//

#include <stdio.h>
#include "cam.h"
#include "math.h"

int width, height;		// camera resolution
float fov;				// vertical field of view (rad)
Vec3Df origin;			// camera origin
MATRIX camToWorld;		// transforms from pixel space to world space

int getWidth() { return width; }
int getHeight() { return height; }

/*
 * Set camera properties such as resolution and field of view.
 */
void setCamProperties(int w, int h, float f)
{
	width = w;
	height = h;
	fov = f;
}

/*
 * Perform all pre-computation for the camera ray casting.
 */
void setCamToWorldMatrix(MATRIX &worldToCamRotation, Vec3Df &camOrigin)
{
	origin = camOrigin;
	Vec3Df w_p = (-width / 2.f) * worldToCamRotation.u + (height / 2.f) * worldToCamRotation.v
				- ( (height / 2.f) / tan(fov * 0.5f) ) * worldToCamRotation.w;
	camToWorld = MATRIX(worldToCamRotation.u, worldToCamRotation.v, w_p);
}

/*
 * Creates a camera ray.
 * By transforming from pixel space (x,y) to world space.
 */
Ray getCamRay(float x, float y)
{
	Vec3Df dir = x * camToWorld.u - y * camToWorld.v + camToWorld.w;	// creates ray and transform (rotates) it.
	dir.normalize();
	return Ray(origin, dir);
}
