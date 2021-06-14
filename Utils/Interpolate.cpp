#include "Interpolate.h"
#include "Math.h"

// between 0 and 1

float MthInterpolateInstant(float t)
{
	return 1.0f;
}

float MthInterpolateLinear(float t)
{
	return t;
}

float MthInterpolateQuadratic(float t)
{
	return t*t;
}

float MthInterpolateCubic(float t)
{
	return t*t*t;
}

float MthInterpolateQuartic(float t)
{
	return t*t*t*t;
}

float MthInterpolateQuintic(float t)
{
	return t*t*t*t*t;
}

float MthInterpolateCircle(float t)
{
	return 1.0f - sqrt(1.0f - t*t);
}

float MthInterpolateSine(float t)
{
	return -1.0f * cos( t * MthPi/2.0f ) + 1;
}

float MthInterpolateBounce(float t)
{
	t = 1.0f - t;
	float UnknownVar = 7.5625f;
	float TotalSize = 2.75f;
	
	if (t < 1.0f / TotalSize)
		return 1.0f - UnknownVar * t * t;
		
	else if (t < 2.0f / TotalSize)
	{
		t = t - 1.5f / TotalSize;
		return 1.0f - (UnknownVar * t * t + 0.75f);
	}
		
	else if (t < 2.5f / TotalSize)
	{
		t = t - 2.25f / TotalSize;
		return 1.0f - (UnknownVar * t * t + 0.9375f);
	}
		
	else
	{
		t = t - 2.625f / TotalSize;
		return 1.0f - (UnknownVar * t * t + 0.984375f);
	}
}

float MthInterpolateSmooth(float t)
{
	return t * t * (3.0f - ( 2.0f * t));
}

float MthInterpolatePower(float t, float p)
{
	return pow(t, p);
}

float MthInterpolateExponential(float t, float p)
{
	return (exp(p * t) - 1.0f) / ( exp(p) - 1.0f);
}

float MthInterpolateElastic(float t, float p)
{
	return -pow(2.0f, 10.0f * (t - 1.0f)) * sin(((t - 1.0f) - p / 4.0f) * 2.0f * MthPi / p);
}

float MthInterpolateBack(float t, float p)
{
	return t * t * t - t * p * sin(t * MthPi);
}

// with range

float MthInterpolateInstant(float a, float b, float t)
{
	return b;
}

float MthInterpolateLinear(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

float MthInterpolateQuadratic(float a, float b, float t)
{
	return MthInterpolateQuadratic((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateCubic(float a, float b, float t)
{
	return MthInterpolateCubic((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateQuartic(float a, float b, float t)
{
	return MthInterpolateQuartic((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateQuintic(float a, float b, float t)
{
	return MthInterpolateQuintic((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateCircle(float a, float b, float t)
{
	return MthInterpolateCircle((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateSine(float a, float b, float t)
{
	return MthInterpolateSine((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateBounce(float a, float b, float t)
{
	return MthInterpolateBounce((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolateSmooth(float a, float b, float t)
{
	return MthInterpolateSmooth((t - a) / (b - a)) * (b - a) + a;
}

float MthInterpolatePower(float a, float b, float t, float p)
{
	return MthInterpolatePower((t - a) / (b - a), p) * (b - a) + a;
}

float MthInterpolateExponential(float a, float b, float t, float p)
{
	return MthInterpolateExponential((t - a) / (b - a), p) * (b - a) + a;
}

float MthInterpolateElastic(float a, float b, float t, float p)
{
	return MthInterpolateElastic((t - a) / (b - a), p) * (b - a) + a;
}

float MthInterpolateBack(float a, float b, float t, float p)
{
	return MthInterpolateBack((t - a) / (b - a), p) * (b - a) + a;
}