#ifndef _MTHMATH_H_
#define _MTHMATH_H_

#include <cmath>

#define MthPi 3.14159265358979323846f

#define MthClamp( x, min, max ) ( x > max ? max : ( x < min ? min : x ) )
#define MthDegrees( r ) ( r * ( 180.0 / MthPi ) )
#define MthRadians( d ) ( d * ( MthPi / 180.0 ) )

typedef struct
{
	float r, g, b, a;
} MthColor;

#include "MthMatrixColumnMajor.h"
#include "MthVector.h"
#include "MthPlane.h"

// You can change this and the header to:
// MthMatrixRowMajor = D3D9 and earlier
// MthMatrixColumnMajor = OpenGL, D3D10 and later
typedef MthMatrixColumnMajor MthMatrix;

typedef struct
{
	float x, y, w, h;
} MthSquare;

static int __forceinline MthExpand( float n )
{
	return n > 0.0f ? (int)n : (int)n - 1;
};

static void MthMatrixHeighted(MthMatrix& mat, MthVector3& campos, MthVector2& camzoom, MthVector2& camvisible, float height);

static __forceinline bool MthTriangleIsClockwise(const MthVector2& p1, const MthVector2& p2)
{
	return p1.x * p2.y - p1.y * p2.x >= 0.0f;
}

static __forceinline bool MthTriangleIsClockwise(const MthVector3& p1, const MthVector3& p2)
{
	return p1.x * p2.y - p1.y * p2.x >= 0.0f;
}

static __forceinline bool MthTriangleIsClockwise(const MthVector2& p1, const MthVector2& p2, const MthVector2& p3)
{
	// This works by doing the cross product to find the perpendicular in 3D space.
	// A positive z value means clockwise, false is counterclockwise.
	return (p1.x - p2.x) * (p3.y - p2.y) - (p1.y - p2.y) * (p3.x - p2.x) >= 0.0f;
}

static __forceinline bool MthTriangleIsClockwise(const MthVector3& p1, const MthVector3& p2, const MthVector3& p3)
{
	// This works by doing the cross product to find the perpendicular in 3D space.
	// A positive z value means clockwise, false is counterclockwise.
	return (p1.x - p2.x) * (p3.y - p2.y) - (p1.y - p2.y) * (p3.x - p2.x) >= 0.0f;
}

template <typename T>
static __forceinline bool MthIsPowerOfTwo(T v)
{
	return v == 0 && v & (v - 1) == 0;
}

#endif