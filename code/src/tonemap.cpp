#include "tonemap.h"

Vec3Df RGB2X(0.5141364, 0.3238786,  0.16036376);
Vec3Df RGB2Y(0.265068,  0.67023428, 0.06409157);
Vec3Df RGB2Z(0.0241188, 0.1228178,  0.84442666);
Vec3Df XYZ2R(2.5651,   -1.1665,   -0.3986);
Vec3Df XYZ2G(-1.0217,    1.9777,    0.0439);
Vec3Df XYZ2B(0.0753,   -0.2543,    1.1892);

//float findMax(std::vector<std::vector<Vec3Df> > &image)
//{
//	float max = 0;
//	for (int y = 0; y < WindowSize_Y; ++y)
//	{
//		for (unsigned int x = 0; x < WindowSize_X; ++x)
//		{
//			if (image[x][y][0] > max) max = image[x][y][0];
//			if (image[x][y][1] > max) max = image[x][y][1];
//			if (image[x][y][2] > max) max = image[x][y][2];
//		}
//	}
//	return max;
//}

void RGBtoSRGB(Vec3Df *image)
{
	for (int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
			image[i][0] = pow(image[i][0], 1. / 2.2);
			image[i][1] = pow(image[i][1], 1. / 2.2);
			image[i][2] = pow(image[i][2], 1. / 2.2);
		}
	}
}

ToneMap::ToneMap()
{
}


ToneMap::~ToneMap()
{
}

void ToneMap::RGBtoYxy(Vec3Df *rgb)
{
	double W;
	for (int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
			float X = Vec3Df::dotProduct(rgb[i], RGB2X);
			float Y = Vec3Df::dotProduct(rgb[i], RGB2Y);
			float Z = Vec3Df::dotProduct(rgb[i], RGB2Z);
			
			W = X + Y + Z;
			if (W > 0.)
			{
				rgb[i][0] = Y;
				rgb[i][1] = X / W;
				rgb[i][2] = Y / W;
			} else {
				rgb[i][0] = 0;
				rgb[i][1] = 0;
				rgb[i][2] = 0;
			}
		}
	}
}

void ToneMap::YxytoRGB(Vec3Df *Yxy)
{
	float X,Z;
	for (int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
			
			float Y = Yxy[i][0];
			float lower_x = Yxy[i][1];
			float lower_y = Yxy[i][2];

			if (Y > 0. && lower_x > 0. && lower_y > 0.)
			{
				X = (lower_x*Y)/lower_y;
				Z = (X/lower_x) - X - Y;
			} else {
				X = 0;
				Z = 0;
			}
			
			float r = Vec3Df::dotProduct(XYZ2R, Vec3Df(X,Y,Z));
			float g = Vec3Df::dotProduct(XYZ2G, Vec3Df(X,Y,Z));
			float b = Vec3Df::dotProduct(XYZ2B, Vec3Df(X,Y,Z));
			
			Yxy[i][0] = r;
			Yxy[i][1] = g;
			Yxy[i][2] = b;
		}
	}
}

//void ToneMap::reinhard(std::vector<std::vector<Vec3Df> > &image)
//{
//	RGBtoYxy(image);
//	//// compute log average
//	double Lavg = 0;
//	double Lmax = 0;
//	int count = 0;
//	for (int y = 0; y < WindowSize_Y; ++y)
//	{
//		for (unsigned int x = 0; x < WindowSize_X; ++x)
//		{
//			float L = image[x][y][0];
//			if (L > 0)
//			{
//				Lavg += log(L);
//				count++;
//			}
//
//			if (L > Lmax) Lmax = L;
//
////			if (x == 0)
////			{
////				//std::cout << "Lavg = " << Lavg << ", image[x][y][0] = " << image[x][y][0] << std::endl;
////			}
//		}
//	}
//
//	Lavg = exp(Lavg/count);
//
//	std::cout << "Lavg = " << Lavg << std::endl;
//
//	double middle_gray = 0.4;
//	Lmax = Lmax * middle_gray / Lavg;
//	for (int y = 0; y < WindowSize_Y; ++y)
//	{
//		for (unsigned int x = 0; x < WindowSize_X; ++x)
//		{
//			float L = image[x][y][0];
//			// map average to middle-gray
//			float Lnew = L * middle_gray / Lavg;
//
//			// Compress high luminances
//			Lnew = Lnew * (1.0 + Lnew / (Lmax*Lmax)) / (Lnew + 1.0);
//
//			image[x][y][0] = Lnew;
//		}
//	}
//
//	YxytoRGB(image);
//
//	// gamma correction
//	RGBtoSRGB(image);
//}

void ToneMap::exposure(Vec3Df *image, float exposure)
{
	RGBtoYxy(image);

	// exposure mapping
	for (int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
			image[i][0] = 1. - exp(-1.*image[i][0] * exposure);
		}
	}

	YxytoRGB(image);

	// gamma correction
	RGBtoSRGB(image);
}
