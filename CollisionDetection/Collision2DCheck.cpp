#include "Collision2DCheck.h"
#include "CollisionUtility.h"
#undef min
#undef max
#include <algorithm>

// AABB

bool Collision2DCheck_AABB_AABB(const Collision2DAABB& a, const MthVector2& apos, const Collision2DAABB& b, const MthVector2& bpos)
{
	return apos.x - a.HalfWidth < bpos.x + b.HalfWidth &&
		   apos.x + a.HalfWidth > bpos.x - b.HalfWidth &&
		   apos.y - a.HalfHeight < bpos.y + b.HalfHeight &&
		   apos.y + a.HalfHeight > bpos.y - b.HalfHeight;
}

bool Collision2DCheck_AABB_Circle(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos)
{
	/* METHOD:
		Calculates if the circle is closest to an edge or a vertex of the box.
		If it is closest to an edge, treat the circle like an AABB.
		If it is closest to a vertex, check to see if the distance between the vertex and the circle's center is less than the circle's radius.
	*/

	// check if circle center point is inside the box
	if (Collision2DCheck_AABB_Point(a, apos, bpos))
		return true;

	// if circle is to the right of the box
	if (bpos.x > apos.x + a.HalfWidth)
	{
		if (bpos.y > apos.y + a.HalfHeight) // top right point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x + a.HalfWidth, apos.y + a.HalfHeight), bpos, b.Radius);

		else if (bpos.y < apos.y - a.HalfHeight) // bottom right point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x + a.HalfWidth, apos.y - a.HalfHeight), bpos, b.Radius);

		else // right edge
			return bpos.x - b.Radius < apos.x + a.HalfWidth;
	}

	// if circle is to the left of the box
	else if (bpos.x < apos.x - a.HalfWidth)
	{
		if (bpos.y > apos.y + a.HalfHeight) // top left point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x - a.HalfWidth, apos.y + a.HalfHeight), bpos, b.Radius);

		else if (bpos.y < apos.y - a.HalfHeight) // bottom left point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x - a.HalfWidth, apos.y - a.HalfHeight), bpos, b.Radius);

		else // left edge
			return bpos.x + b.Radius > apos.x - a.HalfWidth;
	}

	// if circle is above the box
	else if (bpos.y > apos.y + a.HalfHeight)
	{
		if (bpos.x > apos.x + a.HalfWidth) // top right point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x + a.HalfWidth, apos.y + a.HalfHeight), bpos, b.Radius);

		else if (bpos.x < apos.x - a.HalfWidth) // top left point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x - a.HalfWidth, apos.y + a.HalfHeight), bpos, b.Radius);

		else // top edge
			return bpos.y - b.Radius < apos.y + a.HalfHeight;
	}

	// if circle is below the box
	else if (bpos.y < apos.y - a.HalfHeight)
	{
		if (bpos.x > apos.x + a.HalfWidth) // bottom right point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x + a.HalfWidth, apos.y - a.HalfHeight), bpos, b.Radius);

		else if (bpos.x < apos.x - a.HalfWidth) // bottom left point
			return DistanceBetweenPointsLessThan(MthVector2(apos.x - a.HalfWidth, apos.y - a.HalfHeight), bpos, b.Radius);

		else // bottom edge
			return bpos.y + b.Radius > apos.y - a.HalfHeight;
	}

	return false;
}

bool Collision2DCheck_AABB_CapsuleY(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos)
{
	// This could probably be done better...

	float capsulecircledist = fabs(b.HalfHeight - b.HalfWidth);

	// check box collision
	if (Collision2DCheck_AABB_AABB(a, apos, Collision2DAABB(b.HalfWidth, capsulecircledist), bpos))
		return true;
	
	// check top circle
	MthVector2 circlepos(bpos.x, bpos.y + capsulecircledist);
	Collision2DCircle circle = (b.HalfWidth);
	if (Collision2DCheck_AABB_Circle(a, apos, circle, circlepos))
		return true;
	
	// check bottom circle
	circlepos.y = bpos.y - capsulecircledist;
	return Collision2DCheck_AABB_Circle(a, apos, circle, circlepos);
}

bool Collision2DCheck_AABB_CapsuleX(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos)
{
	// This could probably be done better...

	float capsulecircledist = fabs(b.HalfWidth - b.HalfHeight);

	// check box collision
	if (Collision2DCheck_AABB_AABB(a, apos, Collision2DAABB(capsulecircledist, b.HalfHeight), bpos))
		return true;
	
	// check right circle
	MthVector2 circlepos(bpos.x + capsulecircledist, bpos.y);
	Collision2DCircle circle = (b.HalfHeight);
	if (Collision2DCheck_AABB_Circle(a, apos, circle, circlepos))
		return true;
	
	// check left circle
	circlepos.x = bpos.x - capsulecircledist;
	return Collision2DCheck_AABB_Circle(a, apos, circle, circlepos);
}

bool Collision2DCheck_AABB_ConvexHull(const Collision2DAABB& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(MthVector2(0.0f, 1.0f)); // add box's axes
	axes.push_back(MthVector2(1.0f, 0.0f)); // add box's axes
	axes[0].Normalize();
	GetNormalizedAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);

	// create box's point list
	MthVector2 boxpoints[4] =
	{
		MthVector2(apos.x + a.HalfWidth, apos.y + a.HalfHeight),
		MthVector2(apos.x + a.HalfWidth, apos.y - a.HalfHeight),
		MthVector2(apos.x - a.HalfWidth, apos.y - a.HalfHeight),
		MthVector2(apos.x - a.HalfWidth, apos.y + a.HalfHeight)
	};

	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(boxpoints, 4, -bpos, axis, amin, amax);
		GetProjectionOnAxis(b.GetPoints(), b.PointsCount, axis, bmin, bmax);

		if (amin > bmax || bmin > amax)
			return false;
	}

	return true;
}


bool Collision2DCheck_AABB_Ray(const Collision2DAABB& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	// check if points are in the box
	if (Collision2DCheck_AABB_Point(a, apos, b.p1 + bpos) || Collision2DCheck_AABB_Point(a, apos, b.p2 + bpos))
		return true;

	// check line intersects with aabb's lines
	MthVector2 p1(a.HalfWidth, a.HalfHeight);
	MthVector2 p2(-a.HalfWidth, a.HalfHeight);
	MthVector2 p3(-a.HalfWidth, -a.HalfHeight);
	MthVector2 p4(a.HalfWidth, -a.HalfHeight);
	if (Collision2DCheck_Ray_Ray(b, bpos, Collision2DRay(p1, p2), apos) ||
		Collision2DCheck_Ray_Ray(b, bpos, Collision2DRay(p2, p3), apos) ||
		Collision2DCheck_Ray_Ray(b, bpos, Collision2DRay(p3, p4), apos) ||
		Collision2DCheck_Ray_Ray(b, bpos, Collision2DRay(p4, p1), apos))
		return true;

	return false;
}

bool Collision2DCheck_AABB_Point(const Collision2DAABB& a, const MthVector2& apos, const MthVector2& b)
{
	return apos.x - a.HalfWidth < b.x &&
		   apos.x + a.HalfWidth > b.x &&
		   apos.y - a.HalfHeight < b.y &&
		   apos.y + a.HalfHeight > b.y;
}

// Circle

bool Collision2DCheck_Circle_Circle(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos)
{
	return (apos - bpos).LengthSqr() < (a.Radius + b.Radius) * (a.Radius + b.Radius);
}

bool Collision2DCheck_Circle_CapsuleY(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos)
{
	// This could probably be done better...

	float capsulecircledist = fabs(b.HalfHeight - b.HalfWidth);
	
	// check top circle
	MthVector2 circlepos(bpos.x, bpos.y + capsulecircledist);
	Collision2DCircle circle(b.HalfWidth);
	if (Collision2DCheck_Circle_Circle(a, apos, circle, circlepos))
		return true;
	
	// check bottom circle
	circlepos.y = bpos.y - capsulecircledist;
	if (Collision2DCheck_Circle_Circle(a, apos, circle, circlepos))
		return true;

	// check box collision
	return Collision2DCheck_AABB_Circle(Collision2DAABB(b.HalfWidth, capsulecircledist), bpos, a, apos);
}

bool Collision2DCheck_Circle_CapsuleX(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos)
{
	// This could probably be done better...

	float capsulecircledist = fabs(b.HalfWidth - b.HalfHeight);
	
	// check right circle
	MthVector2 circlepos(bpos.x + capsulecircledist, bpos.y);
	Collision2DCircle circle(b.HalfHeight);
	if (Collision2DCheck_Circle_Circle(a, apos, circle, circlepos))
		return true;
	
	// check left circle
	circlepos.x = bpos.x - capsulecircledist;
	if (Collision2DCheck_Circle_Circle(a, apos, circle, circlepos))
		return true;

	// check box collision
	return Collision2DCheck_AABB_Circle(Collision2DAABB(capsulecircledist, b.HalfHeight), bpos, a, apos);
}

bool Collision2DCheck_Circle_ConvexHull(const Collision2DCircle& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(b.GetPoints()[FindClosestPoint(b.GetPoints(), b.PointsCount, apos - bpos)] + bpos - apos); // axis from hull's closest point to circle's center
	axes[0].Normalize();
	GetNormalizedAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	
	float bmin, bmax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(b.GetPoints(), b.PointsCount, bpos, axis, bmin, bmax);
		float aproj = axis.Dot(apos); // calculate circle's projection

		if (aproj - a.Radius > bmax || bmin > aproj + a.Radius)
			return false;
	}

	return true;
}

bool Collision2DCheck_Circle_Ray(const Collision2DCircle& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	MthVector2 closestpoint;
	ClosestPointOnFiniteLine(closestpoint, bpos + b.p1, bpos + b.p2, apos);
	return (closestpoint - apos).Length() <= a.Radius;
}

bool Collision2DCheck_Circle_Point(const Collision2DCircle& a, const MthVector2& apos, const MthVector2& b)
{
	MthVector2 diff = apos - b;
	float lengthsquared = diff.x * diff.x + diff.y * diff.y;
	return lengthsquared < a.Radius * a.Radius;
}

// CapsuleY

bool Collision2DCheck_CapsuleY_CapsuleY(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos)
{
	/* METHOD:
		Check to see if there is horizontal overlap
		Do AABB checks of both capsule's boxes
		Do circle test on top and bottoms (top & top and bottom & bottom will never collide)
	*/
	
	float acircledist = fabs(a.HalfHeight - a.HalfWidth);
	float bcircledist = fabs(a.HalfHeight - a.HalfWidth);

	// is to the right
	if (apos.x - a.HalfWidth > bpos.x + b.HalfWidth)
		return false;
	
	// is to the left
	if (apos.x + a.HalfWidth < bpos.x - b.HalfWidth)
		return false;
	
	// aabb collision
	if (apos.y - acircledist < bpos.y + bcircledist &&
		apos.y + acircledist > bpos.y - bcircledist)
		return true;
	
	
	// check top circle with bottom circle
	MthVector2 acirclepos(apos.x, apos.y + acircledist);
	Collision2DCircle acircle(a.HalfWidth);

	MthVector2 bcirclepos(bpos.x, bpos.y - bcircledist);
	Collision2DCircle bcircle(b.HalfWidth);

	if (Collision2DCheck_Circle_Circle(acircle, acirclepos, bcircle, bcirclepos))
		return true;
	
	// check bottom circle with top circle
	acirclepos.y = apos.y - acircledist;
	bcirclepos.y = bpos.y + bcircledist;
	return Collision2DCheck_Circle_Circle(acircle, acirclepos, bcircle, bcirclepos);
}

bool Collision2DCheck_CapsuleY_CapsuleX(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos)
{
	// This could probably be done better...
	
	float acircledist = fabs(a.HalfHeight - a.HalfWidth);
	Collision2DAABB abox(a.HalfWidth, acircledist);
	Collision2DCircle acircle(a.HalfWidth);
	MthVector2 atopcircle(apos.x, apos.y + acircledist);
	MthVector2 abottomcircle(apos.x, apos.y - acircledist);
	
	float bcircledist = b.HalfWidth - b.HalfHeight;
	Collision2DAABB bbox(bcircledist, b.HalfHeight);
	Collision2DCircle bcircle(b.HalfHeight);
	MthVector2 brightcircle(bpos.x + bcircledist, bpos.y);
	MthVector2 bleftcircle(bpos.x - bcircledist, bpos.y);

	// do the same shape test first (for speed)
	if (Collision2DCheck_AABB_AABB(abox, apos, bbox, bpos) ||
		Collision2DCheck_Circle_Circle(acircle, atopcircle, bcircle, brightcircle) ||
		Collision2DCheck_Circle_Circle(acircle, atopcircle, bcircle, bleftcircle) ||
		Collision2DCheck_Circle_Circle(acircle, abottomcircle, bcircle, brightcircle) ||
		Collision2DCheck_Circle_Circle(acircle, abottomcircle, bcircle, bleftcircle))
		return true;

	// check with different shapes
	if (Collision2DCheck_AABB_Circle(abox, apos, bcircle, brightcircle) ||
		Collision2DCheck_AABB_Circle(abox, apos, bcircle, bleftcircle) ||
		Collision2DCheck_AABB_Circle(bbox, bpos, acircle, atopcircle) ||
		Collision2DCheck_AABB_Circle(bbox, bpos, acircle, abottomcircle))
		return true;
	
	return false;
}

bool Collision2DCheck_CapsuleY_ConvexHull(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfHeight - a.HalfWidth);

	if (Collision2DCheck_AABB_ConvexHull(Collision2DAABB(a.HalfWidth, capsulecircledist), apos, b, bpos))
		return true;

	if (Collision2DCheck_Circle_ConvexHull(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y + capsulecircledist), b, bpos))
		return true;

	if (Collision2DCheck_Circle_ConvexHull(Collision2DCircle(a.HalfWidth), MthVector2(apos.x, apos.y - capsulecircledist), b, bpos))
		return true;

	return false;
}

bool Collision2DCheck_CapsuleY_Ray(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfHeight - a.HalfWidth);

	if (Collision2DCheck_AABB_Ray(Collision2DAABB(a.HalfWidth, capsulecircledist), apos, b, bpos))
		return true;

	if (Collision2DCheck_Circle_Ray(Collision2DCircle(capsulecircledist), MthVector2(apos.x, apos.y + capsulecircledist), b, bpos))
		return true;

	if (Collision2DCheck_Circle_Ray(Collision2DCircle(capsulecircledist), MthVector2(apos.x, apos.y - capsulecircledist), b, bpos))
		return true;

	return false;
}

bool Collision2DCheck_CapsuleY_Point(const Collision2DCapsuleY& a, const MthVector2& apos, const MthVector2& b)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfHeight - a.HalfWidth);

	// check box collision
	if (Collision2DCheck_AABB_Point(Collision2DAABB(a.HalfWidth, capsulecircledist), apos, b))
		return true;
	
	// check top circle
	MthVector2 circlepos(apos.x, apos.y + capsulecircledist);
	Collision2DCircle circle(a.HalfWidth);
	if (Collision2DCheck_Circle_Point(circle, circlepos, b))
		return true;
	
	// check bottom circle
	circlepos.y = apos.y - capsulecircledist;
	return Collision2DCheck_Circle_Point(circle, circlepos, b);
}

// CapsuleX

bool Collision2DCheck_CapsuleX_CapsuleX(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos)
{
	/* METHOD:
		Check to see if there is vertical overlap
		Do AABB checks of both capsule's boxes
		Do circle test on left and right (left & left and right & right will never collide)
	*/
	
	float acircledist = fabs(a.HalfWidth - a.HalfHeight);
	float bcircledist = fabs(b.HalfWidth - b.HalfHeight);

	// is above
	if (apos.y - a.HalfHeight > bpos.y + b.HalfHeight)
		return false;
	
	// is below
	if (apos.y + a.HalfHeight < bpos.y - b.HalfHeight)
		return false;
	
	// aabb collision
	if (apos.x - acircledist < bpos.x + bcircledist &&
		apos.x + acircledist > bpos.x - bcircledist)
		return true;
	
	
	// check right circle with left circle
	MthVector2 acirclepos(apos.x + acircledist, apos.y);
	Collision2DCircle acircle(a.HalfHeight);

	MthVector2 bcirclepos(bpos.x - bcircledist, bpos.y);
	Collision2DCircle bcircle(b.HalfHeight);

	if (Collision2DCheck_Circle_Circle(acircle, acirclepos, bcircle, bcirclepos))
		return true;
	
	// check left circle with right circle
	acirclepos.x = apos.x - acircledist;
	bcirclepos.x = bpos.x + bcircledist;
	return Collision2DCheck_Circle_Circle(acircle, acirclepos, bcircle, bcirclepos);
}

bool Collision2DCheck_CapsuleX_ConvexHull(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfWidth - a.HalfHeight);

	if (Collision2DCheck_AABB_ConvexHull(Collision2DAABB(capsulecircledist, a.HalfHeight), apos, b, bpos))
		return true;

	if (Collision2DCheck_Circle_ConvexHull(Collision2DCircle(capsulecircledist), MthVector2(apos.x + capsulecircledist, apos.y), b, bpos))
		return true;

	if (Collision2DCheck_Circle_ConvexHull(Collision2DCircle(capsulecircledist), MthVector2(apos.x - capsulecircledist, apos.y), b, bpos))
		return true;

	return false;
}

bool Collision2DCheck_CapsuleX_Ray(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfWidth - a.HalfHeight);

	if (Collision2DCheck_AABB_Ray(Collision2DAABB(capsulecircledist, a.HalfHeight), apos, b, bpos))
		return true;

	if (Collision2DCheck_Circle_Ray(Collision2DCircle(capsulecircledist), MthVector2(apos.x + capsulecircledist, apos.y), b, bpos))
		return true;

	if (Collision2DCheck_Circle_Ray(Collision2DCircle(capsulecircledist), MthVector2(apos.x - capsulecircledist, apos.y), b, bpos))
		return true;

	return false;
}

bool Collision2DCheck_CapsuleX_Point(const Collision2DCapsuleX& a, const MthVector2& apos, const MthVector2& b)
{
	// This could probably be done better...
	
	float capsulecircledist = fabs(a.HalfWidth - a.HalfHeight);

	// check box collision
	if (Collision2DCheck_AABB_Point(Collision2DAABB(capsulecircledist, a.HalfHeight), apos, b))
		return true;
	
	// check top circle
	MthVector2 circlepos(apos.x + capsulecircledist, apos.y);
	Collision2DCircle circle(a.HalfHeight);
	if (Collision2DCheck_Circle_Point(circle, circlepos, b))
		return true;
	
	// check bottom circle
	circlepos.x = apos.x - capsulecircledist;
	return Collision2DCheck_Circle_Point(circle, circlepos, b);
}

// ConvexHull

bool Collision2DCheck_ConvexHull_ConvexHull(const Collision2DConvexHull& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	GetAxesFromConvexHull(a.GetPoints(), a.PointsCount, axes);
	GetAxesFromConvexHull(b.GetPoints(), b.PointsCount, axes);
	
	// find out which is larger so then positions can be relative to the larger object
	// this should speed things up quite a bit when calling GetProjectionOnAxis
	bool aislarger = a.PointsCount > b.PointsCount;
	MthVector2 relativeposition = aislarger ? bpos - apos : apos - bpos;

	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
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

		if (amin > bmax || bmin > amax)
			return false;
	}

	return true;
}

bool Collision2DCheck_ConvexHull_Ray(const Collision2DConvexHull& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	// Uses the separate axis theorem (SAT)

	MthVector2 rayaxis = b.p1 - b.p2;
	rayaxis.Normalize();

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(rayaxis);
	axes.push_back(MthVector2(rayaxis.y, rayaxis.x));
	GetNormalizedAxesFromConvexHull(a.GetPoints(), a.PointsCount, axes);
	
	float amin, amax;
	float bmin, bmax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(a.GetPoints(), a.PointsCount, apos, axis, amin, amax);
		bmin = axis.Dot(bpos + b.p1);
		bmax = axis.Dot(bpos + b.p2);
		if (bmin > bmax) std::swap(bmin, bmax);

		if (bmin > amax || amin > bmax)
			return false;
	}

	return true;
}

bool Collision2DCheck_ConvexHull_Point(const Collision2DConvexHull& a, const MthVector2& apos, const MthVector2& b)
{
	// Uses the separate axis theorem (SAT)

	// get axes
	std::vector<MthVector2> axes;
	axes.push_back(a.GetPoints()[FindClosestPoint(a.GetPoints(), a.PointsCount, b - apos)] - b); // axis from hull's closest point to point
	axes[0].Normalize();
	GetNormalizedAxesFromConvexHull(a.GetPoints(), a.PointsCount, axes);
	
	float amin, amax;
	for (auto& axis : axes)
	{
		GetProjectionOnAxis(a.GetPoints(), a.PointsCount, apos, axis, amin, amax);
		float bproj = axis.Dot(apos); // calculate points projection

		if (bproj > amax || amin > bproj)
			return false;
	}

	return true;
}

// Ray

bool Collision2DCheck_Ray_Ray(const Collision2DRay& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos)
{
	// Store the values for fast access and easy
	// equations-to-code conversion
	float x1 = a.p1.x + apos.x;
	float x2 = a.p2.x + apos.x;
	float x3 = b.p1.x + bpos.x;
	float x4 = b.p2.x + bpos.x;

	float y1 = a.p1.y + apos.y;
	float y2 = a.p2.y + apos.y;
	float y3 = b.p1.y + bpos.y;
	float y4 = b.p2.y + bpos.y;
 
	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0)
		return false;
 
	// Get the x and y
	float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
	float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
	// Check if the x and y coordinates are within both lines
	const float epsilon = 1e-5f;
	if (x < (std::min(x1, x2) - epsilon) || x > (std::max(x1, x2) + epsilon) || x < (std::min(x3, x4) - epsilon) || x > (std::max(x3, x4) + epsilon))
		return false;
	if (y < (std::min(y1, y2) - epsilon) || y > (std::max(y1, y2) + epsilon) || y < (std::min(y3, y4) - epsilon) || y > (std::max(y3, y4) + epsilon))
		return false;

	return true;

	/*
	// Return the point of intersection
	Point* ret = new Point();
	ret->x = x;
	ret->y = y;
	return ret;
	*/
};

// collision checker

typedef bool (*ColFnc)(const Collision2DShape&, const MthVector2&, const Collision2DShape&, const MthVector2&);
static ColFnc Collision2DCheckFunctions[6][6] =
{
	{(ColFnc)Collision2DCheck_AABB_AABB,(ColFnc)Collision2DCheck_AABB_Circle,	(ColFnc)Collision2DCheck_AABB_CapsuleY,		(ColFnc)Collision2DCheck_AABB_CapsuleX,		(ColFnc)Collision2DCheck_AABB_ConvexHull,		(ColFnc)Collision2DCheck_AABB_Ray},
	{(ColFnc)nullptr,					(ColFnc)Collision2DCheck_Circle_Circle,	(ColFnc)Collision2DCheck_Circle_CapsuleY,	(ColFnc)Collision2DCheck_Circle_CapsuleX,	(ColFnc)Collision2DCheck_Circle_ConvexHull,		(ColFnc)Collision2DCheck_Circle_Ray},
	{(ColFnc)nullptr,					(ColFnc)nullptr,						(ColFnc)Collision2DCheck_CapsuleY_CapsuleY,	(ColFnc)Collision2DCheck_CapsuleY_CapsuleX,	(ColFnc)Collision2DCheck_CapsuleY_ConvexHull,	(ColFnc)Collision2DCheck_CapsuleY_Ray},
	{(ColFnc)nullptr,					(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)Collision2DCheck_CapsuleX_CapsuleX,	(ColFnc)Collision2DCheck_CapsuleX_ConvexHull,	(ColFnc)Collision2DCheck_CapsuleX_Ray},
	{(ColFnc)nullptr,					(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)nullptr,							(ColFnc)Collision2DCheck_ConvexHull_ConvexHull,	(ColFnc)Collision2DCheck_ConvexHull_Ray},
	{(ColFnc)nullptr,					(ColFnc)nullptr,						(ColFnc)nullptr,							(ColFnc)nullptr,							(ColFnc)nullptr,								(ColFnc)Collision2DCheck_Ray_Ray},
};

bool Collision2DCheck(const Collision2DShape& a, const MthVector2& apos, const Collision2DShape&b, const MthVector2& bpos)
{
	if (Collision2DCheckFunctions[(int)a.Type][(int)b.Type])
		return Collision2DCheckFunctions[(int)a.Type][(int)b.Type](a, apos, b, bpos);
	else if (Collision2DCheckFunctions[(int)b.Type][(int)a.Type])
		return Collision2DCheckFunctions[(int)b.Type][(int)a.Type](b, bpos, a, apos);
	return false;
};

typedef bool (*ColFncPnt)(const Collision2DShape&, const MthVector2&, const MthVector2&);
static ColFncPnt Collision2DCheckFunctionsPoints[6] =
{
	(ColFncPnt)Collision2DCheck_AABB_Point,
	(ColFncPnt)Collision2DCheck_Circle_Point,
	(ColFncPnt)Collision2DCheck_CapsuleY_Point,
	(ColFncPnt)Collision2DCheck_CapsuleX_Point,
	(ColFncPnt)Collision2DCheck_ConvexHull_Point,
	(ColFncPnt)nullptr,
};

bool Collision2DCheck(const Collision2DShape& a, const MthVector2& apos, const MthVector2& bpos)
{
	if (Collision2DCheckFunctionsPoints[(int)a.Type])
		return Collision2DCheckFunctionsPoints[(int)a.Type](a, apos, bpos);
	return false;
};