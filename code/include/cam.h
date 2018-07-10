#ifndef CAM_H_
#define CAM_H_

#include "ray.h"

struct MATRIX 
{
	Vec3Df u,v,w;	// The three rows of the matrix
	MATRIX() {}
	MATRIX(Vec3Df u_, Vec3Df v_, Vec3Df w_) : u(u_), v(v_), w(w_) {}
};

extern const int width;
extern const int height;

/*
 * Set camera properties such as resolution and field of view.
 */
void setCamProperties(float fov);

/*
 * Set the camera-to-world matrix (rotation) and the origin of the camera.
 */
void setCamToWorldMatrix(MATRIX &worldToCamRotation, Vec3Df &camOrigin);

/*
 * Get the camera ray associated with the pixel coordinate (x,y).
 */
Ray getCamRay(float x, float y);

#endif
