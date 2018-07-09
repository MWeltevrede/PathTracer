#ifndef light_h
#define light_h

#include <vector>
#include "Vec3D.h"
#include "ray.h"
#include "BVH.h"

// Class for sampling rectangular light sources.
class LightRectangle
{
	public:
		LightRectangle() {};

		void initialiseLight(Vec3Df &origin, Vec3Df &axis1, Vec3Df &axis2, Vec3Df &emmision,
							 float width, float height);
	
		Ray randomLightSample(Vec3Df &rayOrigin); // creates a jittered sample from the subdivision
	
		Vec3Df getEmmision() {return emmision;}
		Vec3Df getNormal() {return normal;}
	
	private:
		Vec3Df axis1;
		Vec3Df axis2;
		Vec3Df origin;
		Vec3Df emmision;
		Vec3Df normal;
		float width;
		float height;
};

/*
 * Class for sampling spherical lights
 */
class LightSphere
{
	public:
		LightSphere() {};
	
		void initialiseLight(Vec3Df &origin, float radius, Vec3Df &emmision);

		Ray jitteredSample(Vec3Df &rayOrigin); // creates a jittered sample from the subdivision
	
	private:
		float radius;
		Vec3Df origin;
		Vec3Df emmision;

		// mapping that preserves fractional area, is bicontinues and has low distortion
		std::pair<float, float> concentricMap(std::pair<float, float> pair);
};


#endif
