#pragma once
#include "Vec3D.h"
#include <vector>
#include <algorithm>
#include <math.h>

extern const int width;//window resolution width
extern const int height;//window resolution height

class ToneMap
{
public:
	ToneMap();
	~ToneMap();

	static void reinhard(std::vector<std::vector<Vec3Df> > &RGB);
	static void exposure(Vec3Df *image, float exposure);

private:
	static void RGBtoYxy(Vec3Df *RGB);
	static void YxytoRGB(Vec3Df *Yxy);
};

