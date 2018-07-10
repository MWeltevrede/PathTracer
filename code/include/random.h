//
//  random.h
//  Pathtracer
//
//  Created by Max Weltevrede on 10/07/2018.
//

#ifndef random_h
#define random_h

#include <random>

// Uniform random number generator [0, 1)
std::random_device rd;	// seed
std::mt19937 gen(rd());	// Mersenne twister seeded with rd
std::uniform_real_distribution<double> dis(0.0, 1.0);

#endif /* random_h */
