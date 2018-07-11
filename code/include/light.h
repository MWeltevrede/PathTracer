#ifndef light_h
#define light_h

#include <vector>
#include "Vec3D.h"
#include "ray.h"
//#include "BVH.h"

class Light
{
	public:
	Light() {};
	virtual ~Light() {}
	Vec3Df getEmmision() {return emmision;}
	
	virtual Ray randomLightSample(Vec3Df &rayOrigin, float &distance) {return Ray();}
	virtual float computeDirectIlluminationWeight(Ray &r, float distance_squared) {return 0.f;}
	
	protected:
	Vec3Df origin;
	Vec3Df emmision;
};

// Class for sampling rectangular light sources.
class LightRectangle : public Light
{
	public:
		LightRectangle() {};
		virtual ~LightRectangle() {}

		void light_init(Vec3Df &origin, Vec3Df &axis1, Vec3Df &axis2, Vec3Df &emmision,
							 float width, float height);
		Vec3Df getNormal() {return normal;}
	
		virtual Ray randomLightSample(Vec3Df &rayOrigin, float &distance);
		virtual float computeDirectIlluminationWeight(Ray &r, float distance_squared);
	
	private:
		Vec3Df axis1;
		Vec3Df axis2;
		Vec3Df normal;
		float width;
		float height;
};

/*
 * Class for sampling spherical lights
 */
class LightSphere : public Light
{
	public:
		LightSphere() {};
		virtual ~LightSphere() {}
	
		void light_init(Vec3Df &origin, float radius, Vec3Df &emmision);
	
		virtual Ray randomLightSample(Vec3Df &rayOrigin, float &distance);
		virtual float computeDirectIlluminationWeight(Ray &r, float distance_squared);
	
	private:
		float radius;
	
		// mapping that preserves fractional area, is bicontinues and has low distortion
		std::pair<float, float> concentricMap(std::pair<float, float> pair);
};


#endif
