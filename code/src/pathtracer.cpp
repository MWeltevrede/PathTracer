//
//  pathtracer.cpp
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#include <stdio.h>
#include "pathtracer.h"
#include "random.h"

/*
 * Randomly samples a light source.
 * Returns p*L
 * where p is the probability for sampling the particular lightray.
 */
Vec3Df explicitLightSampling(Intersection &inter)
{
	Vec3Df color = Vec3Df(0,0,0);
	int rand_light = floor(dis(gen)*lights.size());		// pick a random light source to sample
	
	Light l = lights.at(rand_light);
	float distance_to_light = 0;
	Ray light_sample = l.randomLightSample(inter.hp, distance_to_light);
	
	if (isOccluded(light_sample, distance_to_light))
	{
		return color;
	}
	
	float weight = l.computeDirectIlluminationWeight(light_sample, distance_to_light*distance_to_light);
	color = l.getEmmision() * weight;

	return color;
}


/*
 * Path tracer radiance function.
 */
Vec3Df PT::computeRadiance(Ray &r)
{
	Vec3Df color = Vec3Df(0,0,0);
	Intersection inter;
	
	bool terminated = false;
	bool add_emission = true;
	int depth = 1;
	Vec3Df mask = Vec3Df(1,1,1);
	float rrFactor = 1;
	
	// iterative instead of recursion
	while (!terminated)
	{
		Intersection inter = computeIntersection(r);
		
		if (!inter.hit) break;
		
		// Emission
		if (add_emission && Vec3Df::dotProduct(inter.material.E, inter.material.E) > 0)
		{
			color += mask*inter.material.E;
		}
		
		// Purely Diffuse objects
		if (inter.material.illum == 1)
		{
			// compute diffuse mask
			mask *=  inter.material.Kd;
			
			// Direct lighting
			color += mask * Vec3Df::dotProduct(inter.normal, r.dir) * explicitLightSampling(inter) / M_PI;
			
			// Indirect lighting
			// Hemisphere sampling
			Vec3Df dir = sampleHemiSphere(inter.normal, dis(gen), dis(gen));
			r.origin = inter.hp;
			r.dir = dir;
			add_emission = false;
		}
		
		// russian roulette
		if (depth > 5)
		{
			terminated = true;
			rrFactor = 0;
			mask *= rrFactor;
		}
		
		depth++;
	}

	return color;
}
