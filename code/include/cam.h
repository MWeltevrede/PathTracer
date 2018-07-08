#ifndef CAM_H_
#define CAM_H_

#include "ray.h"

struct MATRIX 
{
	Vec3Df u,v,w;
	MATRIX() {}
	MATRIX(Vec3Df u_, Vec3Df v_, Vec3Df w_) : u(u_), v(v_), w(w_) {}
};

void setCamProperties(int width, int height, float fov);

void setCamToWorldMatrix(MATRIX &worldToCamRotation, Vec3Df &camOrigin);

Ray getCamRay(float x, float y);

#endif
