#include "Timer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Timer::Timer()
{
	QueryPerformanceFrequency( (LARGE_INTEGER*) &Frequency );
	QueryPerformanceCounter( (LARGE_INTEGER*) &Before );
};

float Timer::GetSeconds()
{
	long long After;
	QueryPerformanceCounter( (LARGE_INTEGER*) &After );

	return ( 1.0f / Frequency ) * ( After - Before );
};

long long Timer::GetTicks()
{
	long long After;
	QueryPerformanceCounter( (LARGE_INTEGER*) &After );
	return After - Before;
};

bool Timer::Reset()
{
	QueryPerformanceCounter( (LARGE_INTEGER*) &Before );
	
	return true;
};