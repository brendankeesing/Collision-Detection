#ifndef _COLLISION_UTILITY_H_
#define _COLLISION_UTILITY_H_

#include "../Utils/Math.h"
#include <vector>

static __forceinline bool DistanceBetweenPointsLessThan(const MthVector2& a, const MthVector2& b, const float dist)
{
	MthVector2 distvec = b - a;
	return distvec.x * distvec.x + distvec.y * distvec.y < dist * dist;
}

static __forceinline bool TriangleIsClockwise(const MthVector2& p1, const MthVector2& p2, const MthVector2& p3)
{
	// This works by doing the cross product to find the perpendicular in 3D space.
	// A positive z value means clockwise, false is counterclockwise.
	return (p1.x - p2.x) * (p3.y - p2.y) - (p1.y - p2.y) * (p3.x - p2.x) >= 0.0f;
}

// reduces the amount of points to include only the outter ring and stores them in anti-clockwise order
// returns a new buffer that must be manually deleted
MthVector2* SimplifyConvexHull(const MthVector2 *const points, const int size, int& outsize);

void GetAxesFromConvexHull(const MthVector2 *const points, const int size, std::vector<MthVector2>& out);

void GetNormalizedAxesFromConvexHull(const MthVector2 *const points, const int size, std::vector<MthVector2>& out);

int FindClosestPoint(const MthVector2 *const points, const int size, const MthVector2& position);

// without world position
void GetProjectionOnAxis(const MthVector2 *const points, const int size, const MthVector2& axis, float& min, float& max);

// with world position
void GetProjectionOnAxis(const MthVector2 *const points, const int size, const MthVector2& position, const MthVector2& axis, float& min, float& max);

void CenterPointOfPoints(MthVector2& out, const MthVector2* const points, const int size);

static void ClosestPointOnLine(MthVector2& out, const MthVector2& linestart, const MthVector2& lineend, const MthVector2& point)
{
	out = lineend - linestart;
	out.Normalize();
	out = out * out.Dot(point - linestart) + linestart;
};

static void ClosestPointOnFiniteLine(MthVector2& out, const MthVector2& linestart, const MthVector2& lineend, const MthVector2& point)
{
	out = lineend - linestart;
	float length = out.Length();
	out /= length;
	float w = out.Dot(point - linestart);
	if (w < 0.0f)
		out = linestart;
	else if (w > length)
		out = lineend;
	else
		out = out * w + linestart;
};

// find the closest point on the edge of a circle given another point
static void ClosestPointOnCircle(MthVector2& out, const MthVector2& circlepos, const float circleradius, const MthVector2& point)
{
	out = circlepos + (point - circlepos);
}

#endif