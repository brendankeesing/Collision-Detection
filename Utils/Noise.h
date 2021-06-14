#ifndef _MTHNOISE_H_
#define _MTHNOISE_H_

unsigned int Noise1D(unsigned int a);
float Noise1D(int x);

float Noise2D(int x, int y);
float SmoothNoise2D(int x, int y);
float InterpolatedNoise2D(float x, float y);
float PerlinNoise2D(float x, float y, float persistance, int octaves);
float PerlinNoise2D(float x, float y, float persistance, int octaves, float invfreq);

#endif