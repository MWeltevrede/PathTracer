#ifndef material_h
#define material_h

#include "Vec3D.h"
#include <string>

struct Material
{
	Vec3Df Kd = Vec3Df(0,0,0);      // diffuse
	Vec3Df Ka = Vec3Df(0,0,0);      // ambient
	Vec3Df Ks = Vec3Df(0,0,0);		// specular
	Vec3Df E = Vec3Df(0,0,0);		// emmision
	float Ns = 0;		//
	float Ni = 0;		// Index of refraction
	int illum = 0;		// illumination model
	float Tr = 0;		// transparency
	std::string name = "";
};

#endif 
