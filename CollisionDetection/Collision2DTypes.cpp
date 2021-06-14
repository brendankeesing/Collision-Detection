#include "Collision2DTypes.h"
#undef max // this can cause a clash with a windows header
#include <algorithm>

void Collision2DAABB::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfWidth = HalfWidth;
	aabb.HalfHeight = HalfHeight;
};

void Collision2DAABB::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = sqrtf(HalfWidth * HalfWidth + HalfHeight * HalfHeight);
};

void Collision2DCircle::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfWidth = Radius;
	aabb.HalfHeight = Radius;
};

void Collision2DCircle::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = Radius;
};

void Collision2DCapsuleY::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfWidth = HalfWidth;
	aabb.HalfHeight = HalfHeight;
};

void Collision2DCapsuleY::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = HalfWidth > HalfHeight ? HalfWidth : HalfHeight;
};

void Collision2DCapsuleX::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfWidth = HalfWidth;
	aabb.HalfHeight = HalfHeight;
};

void Collision2DCapsuleX::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = HalfWidth > HalfHeight ? HalfWidth : HalfHeight;
};

void Collision2DConvexHull::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfHeight = aabb.HalfWidth = 0.0f;
	for (int i = 0; i < PointsCount; ++i)
	{
		if (abs(Points[i].x) > aabb.HalfWidth) aabb.HalfWidth = abs(Points[i].x);
		if (abs(Points[i].y) > aabb.HalfHeight) aabb.HalfHeight = abs(Points[i].y);
	}
};

void Collision2DConvexHull::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = 0.0f;
	for (int i = 0; i < PointsCount; ++i)
	{
		if (abs(Points[i].x) > circle.Radius) circle.Radius = abs(Points[i].x);
		if (abs(Points[i].y) > circle.Radius) circle.Radius = abs(Points[i].y);
	}
};

void Collision2DRay::GetAABB(Collision2DAABB& aabb) const
{
	aabb.HalfHeight = std::max(abs(p1.y), abs(p2.y));
	aabb.HalfWidth = std::max(abs(p1.x), abs(p2.x));
};

void Collision2DRay::GetCircle(Collision2DCircle& circle) const
{
	circle.Radius = std::max(std::max(abs(p1.y), abs(p2.y)), std::max(abs(p1.x), abs(p2.x)));
};