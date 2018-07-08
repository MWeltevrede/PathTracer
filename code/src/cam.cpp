//
//  cam.cpp
//  
// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
//  Created by Max Weltevrede on 08/07/2018.
//

#include <stdio.h>
#include "cam.h"
#include "math.h"

int width, height;
float fov;
Vec3Df origin;
MATRIX camToWorld;

void setCamProperties(int w, int h, float f)
{
	width = w;
	height = h;
	fov = f;
}

void setCamToWorldMatrix(MATRIX &worldToCamRotation, Vec3Df &camOrigin)
{
	origin = camOrigin;
	Vec3Df w_p = (-width / 2.f) * worldToCamRotation.u + (height / 2.f) * worldToCamRotation.v
				- ( (height / 2.f) / tan(fov * 0.5f) ) * worldToCamRotation.w;
	camToWorld = MATRIX(worldToCamRotation.u, worldToCamRotation.v, w_p);
}

Ray getCamRay(float x, float y)
{
	Vec3Df dir = x * camToWorld.u - y * camToWorld.v + camToWorld.w;
	dir.normalize();
	return Ray(origin, dir);
}
