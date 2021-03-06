#ifndef render_h
#define render_h

#include "ray.h"
#include "cam.h"
#include "pathtracer.h"
#include <random>


extern const int width;
extern const int height;

/*
 * Initiates the rendering process for the given pixel (x,y).
 * Stores the result in output.
 */
void render_kernel(Vec3Df *output, float x, float y, int spp);

#endif
