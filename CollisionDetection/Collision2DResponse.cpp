#include "Collision2DResponse.h"
#include "CollisionUtility.h"
#undef min
#undef max
#include <algorithm>

// AABB
bool Collision2DResponse_AABB_AABB(const Collision2DAABB& a, const MthVector2& apos, const Collision2DAABB& b, const MthVector2& bpos, Collision2DResult& result)
{
	// calculate edges
	float left = (bpos.x - b.HalfWidth) - (apos.x + a.HalfWidth);
	float right = (bpos.x + b.HalfWidth) - (apos.x - a.HalfWidth);
	float top = (bpos.y - b.HalfHeight) - (apos.y + a.HalfHeight);
	float bottom = (bpos.y + b.HalfHeight) - (apos.y - a.HalfHeight);

	// check to see if there is no overlap on each axes
	if ((left > 0.0f) == (right > 0.0f) ||
		(bottom > 0.0f) == (top > 0.0f))
		return false;
	
	// compare on x-axis
	if (fabs(left) < right)
		result.Direction.x = left;
	else
		result.Direction.x = right;

	// compare on y-axis
	if (fabs(top) < bottom)
		result.Direction.y = top;
	else
		result.Direction.y = bottom;
	
	// do not move on the axis that requires more movement than the other
	if (fabs(result.Direction.x) < fabs(result.Direction.y))
		result.Direction.y = 0;
	else
		result.Direction.x = 0;

	return true;
}

bool Collision2DResponse_AABB_Circle(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos, Collision2DResult& result)
{
	MthVector2 diff = apos - bpos;

	// if circle center point is in the box
	if (bpos.x > apos.x - a.HalfWidth && bpos.x < apos.x + a.HalfWidth && bpos.y > apos.y - a.HalfHeight && bpos.y < apos.y + a.HalfHeight)
	{
		// horizontal check
		if (abs(diff.x) > abs(diff.y))
		{
			const float combinedradius = b.Radius + a.HalfWidth;
			if (diff.x > combinedradius || diff.x < -combinedradius)
				return false;
			result.Direction.y = 0.0f;
			result.Direction.x = (diff.x > 0.0f ? combinedradius : -combinedradius) - diff.x;
			return true;
		}

		// vertical check
		const float combinedradius = b.Radius + a.HalfHeight;
		if (diff.y > combinedradius || diff.y < -combinedradius)
			return false;
		result.Direction.x = 0.0f;
		result.Direction.y = (diff.y > 0.0f ? combinedradius : -combinedradius) - diff.y;
		return true;
	}

	// horizontal check
	if (bpos.x >= apos.x + a.HalfWidth || bpos.x <= apos.x - a.HalfWidth)
	{
		// corner check
		if (bpos.y >= apos.y + a.HalfHeight || bpos.y <= apos.y - a.HalfHeight)
		{
			MthVector2 diff = bpos - apos;
			if (diff.x > 0.0f)
			{
				if (diff.y > 0.0f)
					return Collision2DResponse_Circle_Point(b, bpos, MthVector2(apos.x + a.HalfWidth, apos.y + a.HalfHeight), result); // top right point
				else
					return Collision2DResponse_Circle_Point(b, bpos, MthVector2(apos.x + a.HalfWidth, apos.y - a.HalfHeight), result); // bottom right point
			}
			else
			{
				if (diff.y > 0.0f)
					return Collision2DResponse_Circle_Point(b, bpos, MthVector2(apos.x - a.HalfWidth, apos.y + a.HalfHeight), result); // top left point
				else
					return Collision2DResponse_Circle_Point(b, bpos, MthVector2(apos.x - a.HalfWidth, apos.y - a.HalfHeight), result); // bottom left point
			}
		}

		// horizontal check
		else
		{
			const float combinedradius = b.Radius + a.HalfWidth;
			if (diff.x > combinedradius || diff.x < -combinedradius)
				return false;
			result.Direction.y = 0.0f;
			result.Direction.x = (diff.x > 0.0f ? combinedradius : -combinedradius) - diff.x;
			return true;
		}
	}

	// vertical check
	const float combinedradius = b.Radius + a.HalfHeight;
	if (diff.y > combinedradius || diff.y < -combinedradius)
		return false;
	result.Direction.x = 0.0f;
	result.Direction.y = (diff.y > 0.0f ? combinedradius : -combinedradius) - diff.y;
	return true;
}

bool Collision2DResponse_AABB_CapsuleY(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result)
{
	const float circledist = abs(b.HalfHeight - b.HalfWidth);

	// top circle
	if (apos.y > bpos.y + circledist)
		return Collision2DResponse_AABB_Circle(a, apos, Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y + circledist), result);

	// bottom circle
	if (apos.y < bpos.y - circledist)
		return Collision2DResponse_AABB_Circle(a, apos, Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y - circledist), result);

	// box check
	float xdiff = bpos.x - apos.x;
	const float combinedradius = a.HalfWidth + b.HalfWidth;

	// if no horizontal collision
	if (abs(xdiff) > combinedradius)
		return false;

	result.Direction = MthVector2(xdiff + (xdiff > 0.0f ? -combinedradius : combinedradius), 0.0f);
	return true;
}

bool Collision2DResponse_AABB_CapsuleX(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result)
{
	const float circledist = abs(b.HalfWidth - b.HalfHeight);

	// top circle
	if (apos.x > bpos.x + circledist)
		return Collision2DResponse_AABB_Circle(a, apos, Collision2DCircle(b.HalfHeight), MthVector2(bpos.x + circledist, bpos.y), result);

	// bottom circle
	if (apos.x < bpos.x - circledist)
		return Collision2DResponse_AABB_Circle(a, apos, Collision2DCircle(b.HalfHeight), MthVector2(bpos.x - circledist, bpos.y), result);

	// box check
	float ydiff = bpos.y - apos.y;
	const float combinedradius = a.HalfHeight + b.HalfHeight;

	// if no horizontal collision
	if (abs(ydiff) > combinedradius)
		return false;

	result.Direction = MthVector2(0.0f, ydiff + (ydiff > 0.0f ? -combinedradius : combinedradius));
	return true;
}

bool Collision2DResponse_AABB_ConvexHull(const Collision2DAABB& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result)
{
	// Uses the separate axis theorem (SAT)

	// get box's points
	MthVector2 boxpoints[4] =
	{
		MthVector2(-a.HalfWidth, a.HalfHeight),
		MthVector2(-a.HalfWidth, -a.HalfHeight),
		MthVector2(a.HalfWidth, -a.HalfHeight),
		MthVector2(a.HalfWidth, a.HalfHeight)
	};

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(MthVector2(0.0f, 1.0f)); // box's axis
	axes.push_back(MthVector2(1.0f, 0.0f)); // box's axis
	GetNormalizedAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	
	float smallestoverlap = 99999999.0f; // very high value
	MthVector2* smallestaxis = nullptr;

	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(boxpoints, 4, apos, axis, amin, amax);
		GetProjectionOnAxis(b.GetPoints(), b.PointsCount, bpos, axis, bmin, bmax);

		// if no collision
		if (amin > bmax || bmin > amax)
			return false;

		// find overlap
		float overlap = amax - bmin;
		const float alternateoverlap = bmax - amin;
		if (abs(overlap) > abs(alternateoverlap))
			overlap = -alternateoverlap;

		// check to see if it is the smallest
		if (abs(overlap) < abs(smallestoverlap))
		{
			smallestoverlap = overlap;
			smallestaxis = &axis;
		}
	}

	result.Direction = *smallestaxis * -smallestoverlap;

	return true;
}

bool Collision2DResponse_AABB_Point(const Collision2DAABB& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result)
{
	MthVector2 diff = b - apos;

	// horizontal collision
	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > a.HalfWidth || diff.x < -a.HalfWidth)
			return false;
		result.Direction.y = 0.0f;
		result.Direction.x = (diff.x > 0.0f ? a.HalfWidth : -a.HalfWidth) - diff.x;
		return true;
	}

	// vertical collision
	if (diff.y > a.HalfHeight || diff.y < -a.HalfHeight)
		return false;
	result.Direction.y = (diff.y > 0.0f ? a.HalfHeight : -a.HalfHeight) - diff.y;
	result.Direction.x = 0.0f;
	return true;
}

// Circle

bool Collision2DResponse_Circle_Circle(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos, Collision2DResult& result)
{
	MthVector2 diff = apos - bpos;
	float length = sqrtf(diff.x * diff.x + diff.y * diff.y);
	if (length < a.Radius + b.Radius)
	{
		result.Direction = diff / length * (a.Radius + b.Radius - length);
		return true;
	}
	return false;
}

bool Collision2DResponse_Circle_CapsuleY(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result)
{
	const float circledist = abs(b.HalfHeight - b.HalfWidth);

	// check with top circle
	if (apos.y >= bpos.y + circledist)
		return Collision2DResponse_Circle_Circle(a, apos, Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y + circledist), result);
	
	// check with bottom circle
	else if (apos.y <= bpos.y - circledist)
		return Collision2DResponse_Circle_Circle(a, apos, Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y - circledist), result);

	// check with box
	float xdiff = apos.x - bpos.x;
	const float combinedradius = a.Radius + b.HalfWidth;
	if (xdiff > combinedradius || xdiff < -combinedradius)
		return false;
	result.Direction.x = (xdiff > 0.0f ? combinedradius : -combinedradius) - xdiff;
	result.Direction.y = 0.0f;
	return true;
}

bool Collision2DResponse_Circle_CapsuleX(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result)
{
	const float circledist = abs(b.HalfWidth - b.HalfHeight);

	// check with right circle
	if (apos.x >= bpos.x + circledist)
		return Collision2DResponse_Circle_Circle(a, apos, Collision2DCircle(b.HalfHeight), MthVector2(bpos.x + circledist, bpos.y), result);
	
	// check with left circle
	else if (apos.x <= bpos.x - circledist)
		return Collision2DResponse_Circle_Circle(a, apos, Collision2DCircle(b.HalfHeight), MthVector2(bpos.x - circledist, bpos.y), result);

	// check with box
	float ydiff = apos.y - bpos.y;
	const float combinedradius = a.Radius + b.HalfHeight;
	if (ydiff > combinedradius || ydiff < -combinedradius)
		return false;
	result.Direction.x = 0.0f;
	result.Direction.y = (ydiff > 0.0f ? combinedradius : -combinedradius) - ydiff;
	return true;
}

bool Collision2DResponse_Circle_ConvexHull(const Collision2DCircle& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(b.GetPoints()[FindClosestPoint(b.GetPoints(), b.PointsCount, apos - bpos)] + bpos - apos); // axis from hull's closest point to circle's center
	axes[0].Normalize();
	GetNormalizedAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	
	float smallestoverlap = 99999999.0f; // very high value
	MthVector2* smallestaxis = nullptr;
	
	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(b.GetPoints(), b.PointsCount, bpos, axis, bmin, bmax);
		amin = axis.Dot(apos); // calculate circle's projection
		amax = amin + a.Radius;
		amin -= a.Radius;

		// if no collision
		if (amin >= bmax || bmin >= amax)
			return false;

		// find overlap
		float overlap = amax - bmin;
		const float alternateoverlap = bmax - amin;
		if (abs(overlap) > abs(alternateoverlap))
			overlap = -alternateoverlap;

		// check to see if it is the smallest
		if (abs(overlap) < abs(smallestoverlap))
		{
			smallestoverlap = overlap;
			smallestaxis = &axis;
		}
	}

	result.Direction = *smallestaxis * -smallestoverlap;

	return true;
}

bool Collision2DResponse_Circle_Point(const Collision2DCircle& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result)
{
	MthVector2 diff = b - apos;
	float length = sqrtf(diff.x * diff.x + diff.y * diff.y);
	result.Direction = diff / length * (a.Radius - length);
	return length < a.Radius;
};

// CapsuleY

bool Collision2DResponse_CapsuleY_CapsuleY(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result)
{
	// if too far away horizontally
	if (abs(apos.x - bpos.x) >= a.HalfWidth + b.HalfWidth)
		return false;
	
	const float acircledist = abs(a.HalfHeight - a.HalfWidth);
	const float bcircledist = abs(b.HalfHeight - b.HalfWidth);

	// A's top circle
	if (apos.y + acircledist < bpos.y - bcircledist)
		return Collision2DResponse_Circle_Circle(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y + acircledist), Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y - bcircledist), result);

	// A's bottom circle
	else if (apos.y - acircledist > bpos.y + bcircledist)
		return Collision2DResponse_Circle_Circle(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y - acircledist), Collision2DCircle(b.HalfWidth), MthVector2(bpos.x, bpos.y + bcircledist), result);

	// horizontal box checks
	float xdiff = apos.x - bpos.x;
	const float combinedradius = a.HalfWidth + b.HalfWidth;
	if (xdiff > combinedradius || xdiff < -combinedradius)
		return false;
	result.Direction.x = (xdiff > 0.0f ? combinedradius : -combinedradius) - xdiff;
	result.Direction.y = 0.0f;
	return true;
}

bool Collision2DResponse_CapsuleY_CapsuleX(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result)
{
	return false;
}

bool Collision2DResponse_CapsuleY_ConvexHull(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result)
{
	return false;
}

bool Collision2DResponse_CapsuleY_Point(const Collision2DCapsuleY& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result)
{
	const float circledist = abs(a.HalfHeight - a.HalfWidth);

	// check with top circle
	if (b.y >= apos.y + circledist)
		return Collision2DResponse_Circle_Point(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y + circledist), b, result);
	
	// check with bottom circle
	else if (b.y <= apos.y - circledist)
		return Collision2DResponse_Circle_Point(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y - circledist), b, result);

	// check with box
	float xdiff = apos.x - b.x;
	if (xdiff > a.HalfWidth || xdiff < -a.HalfWidth)
		return false;
	result.Direction.x = (xdiff > 0.0f ? a.HalfWidth : -a.HalfWidth) - xdiff;
	result.Direction.y = 0.0f;
	return true;
}

// CapsuleX

bool Collision2DResponse_CapsuleX_CapsuleX(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result)
{
	// if too far away vertically
	if (abs(apos.y - bpos.y) >= a.HalfHeight + b.HalfHeight)
		return false;
	
	const float acircledist = abs(a.HalfWidth - a.HalfHeight);
	const float bcircledist = abs(b.HalfWidth - b.HalfHeight);

	// A's right circle
	if (apos.x + acircledist < bpos.x - bcircledist)
		return Collision2DResponse_Circle_Circle(Collision2DCircle(a.HalfHeight), MthVector2(apos.x + acircledist, apos.y), Collision2DCircle(b.HalfHeight), MthVector2(bpos.x - bcircledist, bpos.y), result);

	// A's left circle
	else if (apos.x - acircledist > bpos.x + bcircledist)
		return Collision2DResponse_Circle_Circle(Collision2DCircle(a.HalfHeight), MthVector2(apos.x - acircledist, apos.y), Collision2DCircle(b.HalfHeight), MthVector2(bpos.x + bcircledist, bpos.y), result);

	// vertical box checks
	float ydiff = apos.y - bpos.y;
	const float combinedradius = a.HalfHeight + b.HalfHeight;
	if (ydiff > combinedradius || ydiff < -combinedradius)
		return false;
	result.Direction.x = 0.0f;
	result.Direction.y = (ydiff > 0.0f ? combinedradius : -combinedradius) - ydiff;
	return true;
}

bool Collision2DResponse_CapsuleX_ConvexHull(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result)
{
	return false;
}

bool Collision2DResponse_CapsuleX_Point(const Collision2DCapsuleX& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result)
{
	const float circledist = abs(a.HalfWidth - a.HalfHeight);

	// check with right circle
	if (b.x >= apos.x + circledist)
		return Collision2DResponse_Circle_Point(Collision2DCircle(a.HalfHeight), MthVector2(apos.x + circledist, apos.y), b, result);
	
	// check with left circle
	else if (b.x <= apos.x - circledist)
		return Collision2DResponse_Circle_Point(Collision2DCircle(a.HalfHeight), MthVector2(apos.x - circledist, apos.y), b, result);

	// check with box
	float ydiff = apos.y - b.y;
	if (ydiff > a.HalfHeight || ydiff < -a.HalfHeight)
		return false;
	result.Direction.x = 0.0f;
	result.Direction.y = (ydiff > 0.0f ? a.HalfHeight : -a.HalfHeight) - ydiff;
	return true;
}

// Hull

bool Collision2DResponse_ConvexHull_ConvexHull(Collision2DConvexHull& a, MthVector2& apos, Collision2DConvexHull& b, MthVector2& bpos, Collision2DResult& result)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	//GetAxesFromConvexHull(a.GetPoints(), a.PointsCount, axes);
	//GetAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	GetNormalizedAxesFromConvexHull(a.GetPoints(), a.PointsCount, axes);
	GetNormalizedAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	
	// find out which is larger so then positions can be relative to the larger object
	// this should speed things up quite a bit when calling GetProjectionOnAxis
	bool aislarger = a.PointsCount > b.PointsCount;
	MthVector2 relativeposition = aislarger ? bpos - apos : apos - bpos;
	
	float smallestoverlap = 99999999.0f; // very high value
	MthVector2* smallestaxis = nullptr;

	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
		/* POSSIBLE OPTIMISATION!!
		if (aislarger)
		{
			GetProjectionOnAxis(a.GetPoints(), a.PointsCount, axis, amin, amax);
			GetProjectionOnAxis(b.GetPoints(), b.PointsCount, relativeposition, axis, bmin, bmax);
		}
		else
		{
			GetProjectionOnAxis(a.GetPoints(), a.PointsCount, relativeposition, axis, amin, amax);
			GetProjectionOnAxis(b.GetPoints(), b.PointsCount, axis, bmin, bmax);
		}
		*/
		GetProjectionOnAxis(a.GetPoints(), a.PointsCount, apos, axis, amin, amax);
		GetProjectionOnAxis(b.GetPoints(), b.PointsCount, bpos, axis, bmin, bmax);

		// if no collision
		if (amin > bmax || bmin > amax)
			return false;

		// find overlap
		float overlap = amax - bmin;
		const float alternateoverlap = bmax - amin;
		if (abs(overlap) > abs(alternateoverlap))
			overlap = -alternateoverlap;

		// check to see if it is the smallest
		if (abs(overlap) < abs(smallestoverlap))
		{
			smallestoverlap = overlap;
			smallestaxis = &axis;
		}
	}

	result.Direction = *smallestaxis * -smallestoverlap;

	return true;
}

// collision checker

typedef bool (*ColFnc)(const Collision2DShape&, const MthVector2&, const Collision2DShape&, const MthVector2&, Collision2DResult& result);
static ColFnc Collision2DResponseFunctions[6][6] =
{
	{(ColFnc)Collision2DResponse_AABB_AABB,	(ColFnc)Collision2DResponse_AABB_Circle,	(ColFnc)Collision2DResponse_AABB_CapsuleY,		(ColFnc)Collision2DResponse_AABB_CapsuleX,		(ColFnc)Collision2DResponse_AABB_ConvexHull,		(ColFnc)nullptr},
	{(ColFnc)nullptr,						(ColFnc)Collision2DResponse_Circle_Circle,	(ColFnc)Collision2DResponse_Circle_CapsuleY,	(ColFnc)Collision2DResponse_Circle_CapsuleX,	(ColFnc)Collision2DResponse_Circle_ConvexHull,		(ColFnc)nullptr},
	{(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)Collision2DResponse_CapsuleY_CapsuleY,	(ColFnc)Collision2DResponse_CapsuleY_CapsuleX,	(ColFnc)Collision2DResponse_CapsuleY_ConvexHull,	(ColFnc)nullptr},
	{(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)nullptr,								(ColFnc)Collision2DResponse_CapsuleX_CapsuleX,	(ColFnc)Collision2DResponse_CapsuleX_ConvexHull,	(ColFnc)nullptr},
	{(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)nullptr,								(ColFnc)nullptr,								(ColFnc)Collision2DResponse_ConvexHull_ConvexHull,	(ColFnc)nullptr},
	{(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)nullptr,								(ColFnc)nullptr,								(ColFnc)nullptr,									(ColFnc)nullptr},
};

bool Collision2DResponse(const Collision2DShape& a, const MthVector2& apos, const Collision2DShape&b, const MthVector2& bpos, Collision2DResult& result)
{
	if (Collision2DResponseFunctions[(int)a.Type][(int)b.Type])
		return Collision2DResponseFunctions[(int)a.Type][(int)b.Type](a, apos, b, bpos, result);
	else if (Collision2DResponseFunctions[(int)b.Type][(int)a.Type])
	{
		if (Collision2DResponseFunctions[(int)b.Type][(int)a.Type](b, bpos, a, apos, result))
		{
			result.Direction = -result.Direction; // reverse the direction of response because the shapes were swapped
			return true;
		}
	}
	return false;
};