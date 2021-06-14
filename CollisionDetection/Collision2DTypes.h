#ifndef _COLLISION2D_TYPES_H_
#define _COLLISION2D_TYPES_H_

#include "../Utils/Math.h"
#include "CollisionUtility.h"

enum class Collision2DShapeType
{
	AABB = 0,
	CIRCLE,
	CAPSULEY,
	CAPSULEX,
	CONVEXHULL,
	RAY
};

class Collision2DAABB;
class Collision2DCircle;

class Collision2DShape
{
public:
	Collision2DShape(Collision2DShapeType type) : Type(type) {};

	virtual void GetAABB(Collision2DAABB& aabb) const = 0;
	virtual void GetCircle(Collision2DCircle& circle) const = 0;

	const Collision2DShapeType Type;
};

class Collision2DAABB : public Collision2DShape
{
public:
	Collision2DAABB() : Collision2DShape(Collision2DShapeType::AABB) {};
	Collision2DAABB(float halfwidth, float halfheight) : Collision2DShape(Collision2DShapeType::AABB), HalfWidth(halfwidth), HalfHeight(halfheight) {};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;

	float HalfWidth;
	float HalfHeight;
};

class Collision2DCircle : public Collision2DShape
{
public:
	Collision2DCircle() : Collision2DShape(Collision2DShapeType::CIRCLE) {};
	Collision2DCircle(float radius) : Collision2DShape(Collision2DShapeType::CIRCLE), Radius(radius) {};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;

	float Radius;
};

class Collision2DCapsuleY : public Collision2DShape
{
public:
	Collision2DCapsuleY() : Collision2DShape(Collision2DShapeType::CAPSULEY) {};
	Collision2DCapsuleY(float halfwidth, float halfheight) : Collision2DShape(Collision2DShapeType::CAPSULEY), HalfWidth(halfwidth), HalfHeight(halfheight) {};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;

	float HalfWidth;
	float HalfHeight;
};

class Collision2DCapsuleX : public Collision2DShape
{
public:
	Collision2DCapsuleX() : Collision2DShape(Collision2DShapeType::CAPSULEX) {};
	Collision2DCapsuleX(float halfwidth, float halfheight) : Collision2DShape(Collision2DShapeType::CAPSULEX), HalfWidth(halfwidth), HalfHeight(halfheight) {};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;

	float HalfWidth;
	float HalfHeight;
};

class Collision2DConvexHull : public Collision2DShape
{
public:
	Collision2DConvexHull() : Collision2DShape(Collision2DShapeType::CONVEXHULL), Points(nullptr), PointsCount(0) {};
	Collision2DConvexHull(MthVector2* points, int numpoints) : Collision2DShape(Collision2DShapeType::CONVEXHULL), Points(nullptr), PointsCount(0)  {SetPoints(points, numpoints);};
	Collision2DConvexHull(MthVector2* points, int numpoints, float scale) : Collision2DShape(Collision2DShapeType::CONVEXHULL), Points(nullptr), PointsCount(0) {SetPoints(points, numpoints); Scale(scale);};
	~Collision2DConvexHull() {if (Points) delete[] Points;};

	Collision2DConvexHull(const Collision2DConvexHull& ch) : Collision2DShape(Collision2DShapeType::CONVEXHULL), Points(ch.CopyPoints()), PointsCount(ch.PointsCount) {};
    Collision2DConvexHull& operator=(const Collision2DConvexHull& ch)
	{
		SetPoints(ch.Points, ch.PointsCount);
		return *this;
	};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;
	
	MthVector2* const GetPoints() const
	{
		return Points;
	};

	MthVector2* CopyPoints() const
	{
		MthVector2* points = new MthVector2[PointsCount];
		memcpy(points, Points, sizeof(MthVector2) * PointsCount);
		return points;
	};

	void const SetPoints(MthVector2* points, int numpoints)
	{
		if (Points)
			delete[] Points;

		Points = SimplifyConvexHull(points, numpoints, PointsCount);
	};

	void Scale(float scale)
	{
		for (int i = 0; i < PointsCount; ++i)
			Points[i] *= scale;
	};

	int PointsCount;

private:
	MthVector2* Points;
};

class Collision2DRay : public Collision2DShape
{
public:
	Collision2DRay() : Collision2DShape(Collision2DShapeType::RAY) {};
	Collision2DRay(float x1, float y1, float x2, float y2) : Collision2DShape(Collision2DShapeType::RAY), p1(x1, y1), p2(x2, y2) {};
	Collision2DRay(MthVector2& p1, MthVector2& p2) : Collision2DShape(Collision2DShapeType::RAY), p1(p1), p2(p2) {};
	
	void GetAABB(Collision2DAABB& aabb) const override;
	void GetCircle(Collision2DCircle& circle) const override;

	MthVector2 p1, p2;
};

#endif