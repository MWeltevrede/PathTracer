#include <stdio.h>
#include "light.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

//// Returns a random point on the light source
//Vec3Df LightRectangle::getRandomPoint()
//{
//	// Uniform random number generator [0, 1)
//	std::random_device rd;	// seed
//	std::mt19937 gen(rd());	// Mersenne twister seeded with rd
//	std::uniform_real_distribution<double> dis(0.0, 1.0);
//
//	std::vector<std::pair<float, float> > samples = jitteredSamples();
//	int index = floor(dis(gen) * samples.size());
//	Vec3Df rayDestination = o + axis1 * samples.at(index).first + axis2 * samples.at(index).second;
//	return rayDestination;
//}

//// Calculates and sets all the variables for the subdivision
//void RectangleLight::subdivide(int s)
//{
//	sampleWidth = s;
//	subWidth = width/s;
//	subHeight = height/s;
//}

//void RectangleLight::computeNormal(const Vec3Df &ax1, const Vec3Df &ax2)
//{
//	axis1 = ax1;
//	axis2 = ax2;
//	n = Vec3Df::crossProduct(axis1, axis2);
//	n.normalize();
//}

void LightRectangle::light_init(Vec3Df &o, Vec3Df &ax1, Vec3Df &ax2, Vec3Df &e,
					 float w, float h)
{
	origin = o;
	axis1 = ax1;
	axis2 = ax2;
	emmision = e;
	width = w;
	height = h;
	normal = Vec3Df::crossProduct(axis1, axis2);
	normal.normalize();
	
}

// Function that will generate jittered (stratified) random samples from the subdivision
Ray LightRectangle::randomLightSample(Vec3Df &rayOrigin, float &distance)
{
	// Uniform random number generator [0, 1)
	std::random_device rd;	// seed
	std::mt19937 gen(rd());	// Mersenne twister seeded with rd
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	
	double rand_x = dis(gen);
	double rand_y = dis(gen);
	
	float x = rand_x*width;
	float y = rand_y*height;
	
	Vec3Df dest = origin + x*axis1 + y*axis2;
	Vec3Df dir = dest - rayOrigin;
	distance = sqrt(Vec3Df::dotProduct(dir, dir));
	dir.normalize();
	
	return Ray(rayOrigin, dir);
}

float LightRectangle::computeDirectIlluminationWeight(Ray &r, float distance_squared)
{
	float weight = height * width * abs(Vec3Df::dotProduct(normal, -r.dir)) / distance_squared;
	return weight;
}

//// Returns a random point on the light source
//Vec3Df Disk::getRandomPoint(const Vec3Df &rayOrigin, const Vec3Df &diskOrigin)
//{
//	// Uniform random number generator [0, 1)
//	std::random_device rd;	// seed
//	std::mt19937 gen(rd());	// Mersenne twister seeded with rd
//	std::uniform_real_distribution<double> dis(0.0, 1.0);
//
//	std::vector<std::pair<float, float>> samples = boundingSquare.jitteredSamples();
//
//	// seting up the disk plane with the disk center as origin
//	Vec3Df rayDirection = diskOrigin - rayOrigin;
//	Vec3Df axis1, axis2;
//	rayDirection.getTwoOrthogonals(axis1, axis2);
//	axis1.normalize();
//	axis2.normalize();
//
//	int index = floor(dis(gen) * samples.size());
//	std::pair<float, float> pair = concentricMap(samples.at(index));
//
//	return diskOrigin + pair.first*axis1 + pair.second*axis2;
//}

//// Calculates and sets all the variables for the subdivision
//// Including the bounding square used for sampling
//void Disk::subdivide(int s)
//{
//	boundingSquare.setWidth(2*radius);
//	boundingSquare.setHeight(2*radius);
//	boundingSquare.subdivide(s);
//	sampleWidth = s;
//}

// A mapping from a square to a disk that preserves fractional area,
// is bicontinues (preserves adjacency) and has low distortion
// src= https://pdfs.semanticscholar.org/4322/6a3916a85025acbb3a58c17f6dc0756b35ac.pdf
std::pair<float, float> LightSphere::concentricMap(std::pair<float, float> s)
{
	// concentric mapping
	float a = s.first/radius - 1;
	float b = s.second/radius - 1;		// maps from [0,height] to [-1,1]
	float r, phi;
	
	if (a > -b)			// region 1 or 2
	{
		if (a > b)		// region 1
		{
			r = a;
			phi = (M_PI/4) * b/a;
		} else			// region 2
		{
			r = b;
			phi = (M_PI/4) * (2-a/b);
		}
	} else if (a < b)	// region 3
	{
		r = -a;
		phi = (M_PI/4) * (4 + b/a);
	} else				// region 4
	{
		r = -b;
		if (b != 0)
		{
			phi = (M_PI/4) * (6 - a/b);
		} else
		{
			phi = 0;
		}
	}
	
	float u = (r*radius) * cos(phi);
	float v = (r*radius) * sin(phi);		// maps from [0,1] to [0, radius]
	
	return std::pair<float, float>(u,v);
}

void LightSphere::light_init(Vec3Df &o, float r, Vec3Df &e)
{
	origin = o;
	radius = r;
	emmision = e;
}

Ray LightSphere::randomLightSample(Vec3Df &rayOrigin, float &distance)
{
	Vec3Df normal = origin - rayOrigin;
	normal.normalize();
	Vec3Df axis1, axis2;
	normal.getTwoOrthogonals(axis1, axis2);
	axis1.normalize();
	axis2.normalize();
	
	// Uniform random number generator [0, 1)
	std::random_device rd;	// seed
	std::mt19937 gen(rd());	// Mersenne twister seeded with rd
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	
	double rand_x = dis(gen);
	double rand_y = dis(gen);
	
	float x = rand_x * radius * 2;
	float y = rand_y * radius * 2;
	
	std::pair<float, float> pair = concentricMap(std::pair<float, float>(x,y));
	
	Vec3Df dest = origin + pair.first*axis1 + pair.second*axis2;
	Vec3Df dir = dest - rayOrigin;
	distance = sqrt(Vec3Df::dotProduct(dir, dir));
	dir.normalize();
	
	// Law of cosines
	Vec3Df AB = pair.first*axis1 + pair.second*axis2;
	AB.normalize();
	float cos_theta = Vec3Df::dotProduct(AB, dir);
	float AB_length = sqrt(pair.first*pair.first + pair.second*pair.second);
	float b = -2*AB_length*cos_theta;
	float c = AB_length*AB_length - radius*radius;
	float delta = -b + sqrt(b*b - 4*c) / 2.;		// should always be positive
	distance -= delta;
	
	return Ray(rayOrigin, dir);
}

float LightSphere::computeDirectIlluminationWeight(Ray &r, float distance_squared)
{
	float weight = M_PI * radius * radius / distance_squared;
	return weight;
}



