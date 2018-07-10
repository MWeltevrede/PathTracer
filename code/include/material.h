//
//  material.h
//  Pathtracer
//
//  Created by Max Weltevrede on 09/07/2018.
//

#ifndef material_h
#define material_h

#include "Vec3D.h"
#include <string>

struct Material
{
	Vec3Df Kd;      // diffuse
	Vec3Df Ka;      // ambient
	Vec3Df Ks;		// specular
	Vec3Df E;		// specular
	float Ns;		//
	float Ni;		// Index of refraction
	int illum;		//illumination model
	float Tr;		// transparency
	std::string name;
};

#endif 
