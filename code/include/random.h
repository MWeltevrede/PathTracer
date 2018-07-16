//
//  random.h
//  Pathtracer
//
//  Created by Max Weltevrede on 10/07/2018.
//

#ifndef random_h
#define random_h

#include <math.h>
#include <random>

//class Halton
//{
//public:
//	Halton(int b, unsigned int o) : base(b), offset(o), inv_base(1./b)
//	{
//		memset(n, -1, sizeof(n));	// initialize array to -1
//
//		int i = 0;
//		while (offset > 0)		// convert offset to base base
//		{
//			n[i] = offset % base;
//			offset /= base;
//			i++;
//		}
//	}
//
//	float next()
//	{
//		float result = 0;
//		int i = 0;
//		int p[32];
//		memset(p, -1, sizeof(p));
//		randomPermutation(p);
//
//		while (p[i] >=0)
//		{
//			result += p[i] * pow(inv_base, i+1);
//			i++;
//
//			if (i >=32) break;
//		}
//
//		increaseByOne();
//		return result;
//	}
//
//private:
//	int base;
//	unsigned int offset;
//	float inv_base;
//	int n[32];
//
//	void randomPermutation(int *p)
//	{
//		int size = 0;
//		while (n[size] >=0)
//		{
//			p[size] = n[size];
//			size++;
//		}
//
//		// Uniform random number generator [0, 1)
//		std::random_device rd;	// seed
//		std::mt19937 gen(rd());	// Mersenne twister seeded with rd
//		std::uniform_int_distribution<int> dis;
//
//		for (int i=0; i < size; i++)
//		{
//			dis = std::uniform_int_distribution<>(i,size-1);
//			int rand_index = dis(gen);
//			int temp = p[i];
//			p[i] = p[rand_index];
//			p[rand_index] = temp;
//		}
//	}
//
//	void increaseByOne()
//	{
//		int i = 0;
//		while (n[i] >= 0)
//		{
//			if (n[i] < base - 1)
//			{
//				n[i] = n[i] + 1;
//				return;
//			}
//
//			// n[i] == base - 1
//			n[i] = 0;
//			i++;
//
//			if (i >= 32)	// reset to 1
//			{
//				i = 0;
//				for (int j=1;j<32;j++)
//				{
//					n[j] = -1;
//				}
//				break;
//			}
//		}
//		n[i] = 1;
//	}
//};

class Halton
{
public:
	Halton(int b, unsigned int o) : base(b), offset(o), inv_base(1./b)
	{
		memset(n, -1, sizeof(n));	// initialize array to -1

		int i = 0;
		while (offset > 0)		// convert offset to base base
		{
			n[i] = offset % base;
			offset /= base;
			i++;
		}
	}

	float next()
	{
		float result = 0;
		int i = 0;
		while (n[i] >=0)
		{
			result += n[i] * pow(inv_base, i+1);
			i++;

			if (i >=32) break;
		}

		increaseByOne();
		return result;
	}

private:
	int base;
	unsigned int offset;
	float inv_base;
	int n[32];

	void increaseByOne()
	{
		int i = 0;
		while (n[i] >= 0)
		{
			if (n[i] < base - 1)
			{
				n[i] = n[i] + 1;
				return;
			}

			// n[i] == base - 1
			n[i] = 0;
			i++;

			if (i >= 32)	// reset to 1
			{
				i = 0;
				for (int j=1;j<32;j++)
				{
					n[j] = -1;
				}
				break;
			}
		}
		n[i] = 1;
	}
};

#endif /* random_h */
