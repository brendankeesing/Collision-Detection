#include "Noise.h"
#include <cmath>

static inline float LinearInterpolation(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

// integer v^p
// does not work when p < 0
static int ipow(int v, int p)
{
	int result = 1;
	while (p > 0)
	{
		result *= v;
		--p;
	}
	return result;
}

unsigned int Noise1D(unsigned int a)
{
	unsigned int hi = 16807 * (a >> 16);
	unsigned int lo = 16807 * (a & 0xFFFF);
	lo += (hi & 0x7FFF) << 16;
	lo += hi >> 15;
	if (lo > 2147483647)
		lo -= 2147483647;
	return lo;
}

float Noise1D(int x)
{
	int n = x * 57;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float Noise2D(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float SmoothNoise2D(int x, int y)
{
	float corners = ( Noise2D(x-1, y-1) + Noise2D(x+1, y-1) + Noise2D(x-1, y+1) + Noise2D(x+1, y+1) ) / 16;
	float sides   = ( Noise2D(x-1, y) + Noise2D(x+1, y) + Noise2D(x, y-1) + Noise2D(x, y+1) ) / 8;
	float center  =  Noise2D(x, y) / 4;
	return corners + sides + center;
}

float InterpolatedNoise2D(float x, float y)
{
	int integer_X = (int)x;
	float fractional_X = x - integer_X;

	int integer_Y = (int)y;
	float fractional_Y = y - integer_Y;

	float v1 = SmoothNoise2D(integer_X, integer_Y);
	float v2 = SmoothNoise2D(integer_X + 1, integer_Y);
	float v3 = SmoothNoise2D(integer_X, integer_Y + 1);
	float v4 = SmoothNoise2D(integer_X + 1, integer_Y + 1);

	float i1 = LinearInterpolation(v1, v2, fractional_X);
	float i2 = LinearInterpolation(v3, v4, fractional_X);

	return LinearInterpolation(i1 , i2 , fractional_Y);
}

float PerlinNoise2D(float x, float y, float persistance, int octaves)
{
	float total = 0.0f;
	for (int i = 0; i < octaves; ++i)
	{
		float frequency = (float)ipow(2, i);
		float amplitude = pow(persistance, i);

		total += InterpolatedNoise2D(x * frequency, y * frequency) * amplitude;
	}

	return total;
}

float PerlinNoise2D(float x, float y, float persistance, int octaves, float invfreq)
{
	return PerlinNoise2D(invfreq * x, invfreq * y, persistance, octaves);
}