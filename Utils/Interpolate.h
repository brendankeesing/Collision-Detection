#ifndef _MTHINTERPOLATE_H_
#define _MTHINTERPOLATE_H_

// Interpolation between 0 and 1
float MthInterpolateInstant(float t);
float MthInterpolateLinear(float t);
float MthInterpolateQuadratic(float t);
float MthInterpolateCubic(float t);
float MthInterpolateQuartic(float t);
float MthInterpolateQuintic(float t);
float MthInterpolateCircle(float t);
float MthInterpolateSine(float t);
float MthInterpolateBounce(float t);
float MthInterpolateSmooth(float t);

float MthInterpolatePower(float t, float p);
float MthInterpolateExponential(float t, float p);
float MthInterpolateElastic(float t, float p);
float MthInterpolateBack(float t, float p);

// Ranged interpolation between a and b
float MthInterpolateInstant(float a, float b, float t);
float MthInterpolateLinear(float a, float b, float t);
float MthInterpolateQuadratic(float a, float b, float v);
float MthInterpolateCubic(float a, float b, float t);
float MthInterpolateQuartic(float a, float b, float t);
float MthInterpolateQuintic(float a, float b, float t);
float MthInterpolateCircle(float a, float b, float t);
float MthInterpolateSine(float a, float b, float t);
float MthInterpolateBounce(float a, float b, float t);
float MthInterpolateSmooth(float a, float b, float t);
float MthInterpolatePower(float a, float b, float t, float p);
float MthInterpolateExponential(float a, float b, float t, float p);
float MthInterpolateElastic(float a, float b, float t, float p);
float MthInterpolateBack(float a, float b, float t, float p);

#endif