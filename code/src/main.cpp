#include <stdio.h>
#include <math.h>
#include "cam.h"
#include "Vec3D.h"
#include "BVH.h"
#include "render.h"
#include "tonemap.h"
#include "imageWriter.h"
#include "random.h"

#define PI 3.141592653589

// angles in blender times -1
#define Eul_X -PI / 4
#define Eul_Y -PI / 4
#define Eul_Z -PI / 4

const int width = 400;
const int height = 400;
const int spp = 10;

/*
 * Structures
 */
std::vector<Sphere> spheres;
std::vector<Light *> lights;

// Uniform random number generator [0, 1)
std::random_device rd;	// seed
std::mt19937 gen(rd());	// Mersenne twister seeded with rd
std::uniform_real_distribution<double> dis(0.0, 1.0);


void initScene()
{
	// initialize spheres
	Sphere s1;
	Material m1;
	m1.Kd = Vec3Df(0.75f, 0.25f, 0.25f);
	m1.illum = 1;
	Vec3Df c1 = Vec3Df(103, 0, 0);
	s1.sphere_init(100, c1, m1);
	spheres.push_back(s1);
	
	Sphere s2;
	Material m2;
	m2.Kd = Vec3Df(.25f, .25f, .75f);
	m2.illum = 1;
	Vec3Df c2 = Vec3Df(-103, 0, 0);
	s2.sphere_init(100, c2, m2);
	spheres.push_back(s2);
	
	Sphere s3;
	Material m3;
	m3.Kd = Vec3Df(.75f, .75f, .75f);
	m3.illum = 1;
	Vec3Df c3 = Vec3Df(0, 0, -100);
	s3.sphere_init(100, c3, m3);
	spheres.push_back(s3);
	
	Sphere s4 = Sphere();
	Material m4 = Material();
	m4.Kd = Vec3Df(.75f, .75f, .75f);
	m4.illum = 1;
	Vec3Df c4 = Vec3Df(0, 103, 0);
	s4.sphere_init(100, c4, m4);
	spheres.push_back(s4);
	
	Sphere s5 = Sphere();
	Material m5 = Material();
	m5.Kd = Vec3Df(.75f, .75f, .75f);
	m5.illum = 1;
	Vec3Df c5 = Vec3Df(0, -101, 0);
	s5.sphere_init(100, c5, m5);
	spheres.push_back(s5);
	
	Sphere s7 = Sphere();
	Material m7 = Material();
	m7.Kd = Vec3Df(1.0f, 1.0f, 1.0f);
	m7.illum = 1;
	Vec3Df c7 = Vec3Df(1.5, 0, 3);
	s7.sphere_init(1, c7, m7);
	spheres.push_back(s7);
	
	Sphere s8 = Sphere();
	Material m8 = Material();
	m8.Kd = Vec3Df(1.0f, 1.0f, 1.0f);
	m8.illum = 1;
	Vec3Df c8 = Vec3Df(-1.5, -0.5, 2);
	s8.sphere_init(0.75, c8, m8);
	spheres.push_back(s8);
	
	Sphere s9 = Sphere();
	Material m9 = Material();
	m9.Kd = Vec3Df(0.0f, 0.0f, 0.0f);
	m9.illum = 1;
	m9.E = Vec3Df(2.0f, 1.8f, 1.6f);
	Vec3Df c9 = Vec3Df(0, 3, 3);
	s9.sphere_init(0.25, c9, m9);
	spheres.push_back(s9);
	
	LightSphere *l = new LightSphere();
	l->light_init(c9, 0.25, m9.E);
	lights.push_back(l);
	
	//	{ 1e5f, { 1e5f + 1.0f, 40.8f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { 0.75f, 0.25f, 0.25f }, DIFF }, //Left
	//	{ 1e5f, { -1e5f + 99.0f, 40.8f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .25f, .25f, .75f }, DIFF }, //Right
	//	{ 1e5f, { 50.0f, 40.8f, 1e5f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Back
	//	{ 1e5f, { 50.0f, 40.8f, -1e5f + 600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.00f, 1.00f, 1.00f }, DIFF }, //Frnt
	//	{ 1e5f, { 50.0f, 1e5f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Botm
	//	{ 1e5f, { 50.0f, -1e5f + 81.6f, 81.6f }, { 0.0f, 0.0f, 0.0f }, { .75f, .75f, .75f }, DIFF }, //Top
	//	{ 16.5f, { 27.0f, 16.5f, 47.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DIFF }, // small sphere 1
	//	{ 16.5f, { 73.0f, 16.5f, 78.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DIFF }, // small sphere 2
	//	{ 600.0f, { 50.0f, 681.6f - .77f, 81.6f }, { 2.0f, 1.8f, 1.6f }, { 0.0f, 0.0f, 0.0f }, DIFF }  // Light
}

int main()
{
	initScene();
	
	// camera
	setCamProperties(PI / 2.);
	MATRIX m = MATRIX(Vec3Df(1,0,0), Vec3Df(0,1,0), Vec3Df(0,0,1));
	Vec3Df o = Vec3Df(0, 0, 6.5);
	setCamToWorldMatrix(m, o);
	
	// timing
	clock_t start;
	double duration;
	start = clock();
	
	// Loop through image
	Vec3Df *output = new Vec3Df[width*height];
	Image result(width,height);
	
	for (int i=0; i < width; i++)
	{
		for (int j=0; j < height; j++)
		{
			render_kernel(output, i, j, spp);
		}
	}
	
	ToneMap::exposure(output, 10);
	
	// temporary
	for (int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			int i = (height - 1 - y) * width + x;	// row-major index, (0,0) in bottom left
			result.setPixel(x, y, RGBValue(output[i][0], output[i][1], output[i][2]));
		}
	}
	
	result.writeImage("result.bmp");
	
	duration = (clock() - start) / (double) CLOCKS_PER_SEC;
	std::cout << "Duration: " << duration << " seconds" << std::endl;
	
	for (Light *l : lights)
	{
		delete l;
	}
}

//	// Euler XYZ
//	Vec3Df u = Vec3Df(cos(Eul_Y)*cos(Eul_Z), -cos(Eul_Y)*sin(Eul_Z), sin(Eul_Y));
//	Vec3Df v = Vec3Df(cos(Eul_X)*sin(Eul_Z) + cos(Eul_Z)*sin(Eul_X)*sin(Eul_Y),
//					  cos(Eul_X)*sin(Eul_Z) - sin(Eul_Z)*sin(Eul_X)*sin(Eul_Y),
//					  -cos(Eul_Y)*sin(Eul_X));
//	Vec3Df w = Vec3Df(sin(Eul_X)*sin(Eul_Z) - cos(Eul_X)*cos(Eul_Z)*sin(Eul_Y),
//					  cos(Eul_Z)*sin(Eul_X) + cos(Eul_X)*sin(Eul_Y)*sin(Eul_Z),
//					  cos(Eul_X)*cos(Eul_Y));
//	MATRIX m = MATRIX(u,v,w);
