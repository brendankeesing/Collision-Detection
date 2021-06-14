#include "CollisionUtility.h"
#include <algorithm>
#include <cassert>

MthVector2* SimplifyConvexHull(const MthVector2 *const points, const int size, int& outsize)
{
	// can't do anything if there are no points
	if (size == 0)
		return nullptr;

	// if there are not enough points then just copy
	if (size <= 3)
	{
		MthVector2* newpoints = new MthVector2[size];
		newpoints[0] = points[0];
		if (size >= 2) newpoints[1] = points[1];
		if (size == 3)
		{
			newpoints[2] = points[2];

			// make sure it is anti-clockwise
			if (TriangleIsClockwise(newpoints[0], newpoints[1], newpoints[2]))
			{
				newpoints[1] = newpoints[2];
				newpoints[2] = points[1];
			}
		}
		outsize = size;
		return newpoints;
	}

	// uses Graham's Scan algorithm

	// find the farthest point to the left
	const MthVector2* current = points;
	for (int i = 1; i < size; ++i)
	{
		if (points[i].x < current->x)
			current = points + i;
	}

	struct _Dot
	{
		_Dot(float d, const MthVector2* p) : dot(d), point(p) {};

		float dot;
		const MthVector2* point;
	};

	// get dot product of all points relative to the left-most point
	std::vector<const _Dot> dots;
	dots.push_back(_Dot(1.0f, current)); // push the left-most first
	const MthVector2* point;
	for (int i = 0; i < size; ++i)
	{
		if ((point = points + i) != current)
		{
			// create vector relative to left-most point
			MthVector2 vec(point->x - current->x, point->y - current->y);

			// divide y by vector length (don't need to worry about x in this case)
			dots.push_back(_Dot(vec.y / sqrtf(vec.x * vec.x + vec.y * vec.y), points + i));
		}
	}

	// sort all except for the left-most one (we can safely assume it will be at the start/end)
	std::sort(dots.begin() + 1, dots.end(), [](const _Dot& a, const _Dot& b) {return a.dot < b.dot;});

	// perform tree-penny algorithm on each 3 consecutive points
	for (int i = 1; i < (int)dots.size(); ++i)
	{
		const MthVector2& p1 = *dots[i - 1].point;
		const MthVector2& p2 = *dots[i].point;
		const MthVector2& p3 = i == dots.size() - 1 ? *current : *dots[i + 1].point;

		if (TriangleIsClockwise(p1, p2, p3))
		{
			dots.erase(dots.begin() + i);
			i -= 2;
			if (i <= 0)
				i = 1;
		}
	}

	// copy new points to buffer
	MthVector2* newpoints = new MthVector2[outsize = dots.size()];
	for (int i = 0; i < (int)dots.size(); ++i)
		newpoints[i] = *dots[i].point;

	return newpoints;
}

void GetAxesFromConvexHull(const MthVector2 *const points, const int size, std::vector<MthVector2>& out)
{
	for (int i = 0; i < size; ++i)
	{
		// get edge tangent
		MthVector2 edge = points[i] - points[i == size - 1 ? 0 : i + 1];

		// get perpendicular
		edge = MthVector2(-edge.y, edge.x);

		out.push_back(edge);
	}
}

void GetNormalizedAxesFromConvexHull(const MthVector2 *const points, const int size, std::vector<MthVector2>& out)
{
	for (int i = 0; i < size; ++i)
	{
		// get edge tangent
		MthVector2 edge = points[i] - points[i == size - 1 ? 0 : i + 1];

		// get normalized perpendicular
		edge = MthVector2::Normalize(MthVector2(edge.y, edge.x));

		out.push_back(edge);
	}
}

int FindClosestPoint(const MthVector2 *const points, const int size, const MthVector2& position)
{
	float dist = (points[0] - position).LengthSqr();
	int index = 0;
	float temp;
	for (int i = 1; i < size; ++i)
	{
		temp = (points[i] - position).LengthSqr();
		if (temp < dist)
		{
			dist = temp;
			index = i;
		}
	}

	return index;
}

void GetProjectionOnAxis(const MthVector2 *const points, const int size, const MthVector2& axis, float& min, float& max)
{
	// set initial min and max
	MthVector2 pos = points[0];
	max = min = axis.Dot(pos);

	float p;
	for (int i = 1; i < size; ++i)
	{
		// calculate projection point
		p = axis.Dot(points[i]);

		// see if projection point is new min/max
		if (p < min) min = p;
		else if (p > max) max = p;
	}
}

void GetProjectionOnAxis(const MthVector2 *const points, const int size, const MthVector2& position, const MthVector2& axis, float& min, float& max)
{
	// set initial min and max
	MthVector2 pos = points[0] + position;
	max = min = axis.Dot(pos);

	float p;
	for (int i = 1; i < size; ++i)
	{
		// move to world position
		pos = points[i] + position;

		// calculate projection point
		p = axis.Dot(pos);

		// see if projection point is new min/max
		if (p < min) min = p;
		else if (p > max) max = p;
	}
}

void CenterPointOfPoints(MthVector2& out, const MthVector2* const points, const int size)
{
	assert(points);

	out = MthVector2(0.0f, 0.0f);
	for (int i = 0; i < size; ++i)
		out += points[i];
	out *= 1.0f / size;
}