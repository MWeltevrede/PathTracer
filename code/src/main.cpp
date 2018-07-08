#include <stdio.h>
#include <math.h>
#include "cam.h"
#include "Vec3D.h"

#define PI 3.141592653589

// angles in blender times -1
#define Eul_X -PI / 4
#define Eul_Y -PI / 4
#define Eul_Z -PI / 4

const int width = 1;
const int height = 1;


int main()
{
	setCamProperties(width, height, PI / 2.);
	
	// Euler XYZ
	Vec3Df u = Vec3Df(cos(Eul_Y)*cos(Eul_Z), -cos(Eul_Y)*sin(Eul_Z), sin(Eul_Y));
	Vec3Df v = Vec3Df(cos(Eul_X)*sin(Eul_Z) + cos(Eul_Z)*sin(Eul_X)*sin(Eul_Y),
					  cos(Eul_X)*sin(Eul_Z) - sin(Eul_Z)*sin(Eul_X)*sin(Eul_Y),
					  -cos(Eul_Y)*sin(Eul_X));
	Vec3Df w = Vec3Df(sin(Eul_X)*sin(Eul_Z) - cos(Eul_X)*cos(Eul_Z)*sin(Eul_Y),
					  cos(Eul_Z)*sin(Eul_X) + cos(Eul_X)*sin(Eul_Y)*sin(Eul_Z),
					  cos(Eul_X)*cos(Eul_Y));
	MATRIX m = MATRIX(u,v,w);
//	MATRIX m = MATRIX(Vec3Df(1,0,0), Vec3Df(0,1,0), Vec3Df(0,0,1));
	Vec3Df o = Vec3Df(0,0,0);
	setCamToWorldMatrix(m, o);
	for (int i=0; i < width; i++)
	{
		for (int j=0; j < height; j++)
		{
			Ray r = getCamRay(i + 0.5, j + 0.5);
			
			std::cout << "Ray direction for pixel (" << i << "," << j << ") = " << r.dir << std::endl;
		}
	}
}
