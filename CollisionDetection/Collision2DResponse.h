#ifndef _COLLISION2D_RESPONSE_H_
#define _COLLISION2D_RESPONSE_H_

#include "Collision2DTypes.h"

struct Collision2DResult
{
	MthVector2 Direction;
	//MthVector2 CollisionSurfaceNormal; // this will just be the normalized of Direction
};

// return true on collision

// AABB
bool Collision2DResponse_AABB_AABB(const Collision2DAABB& a, const MthVector2& apos, const Collision2DAABB& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_AABB_Circle(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_AABB_CapsuleY(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_AABB_CapsuleX(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_AABB_ConvexHull(const Collision2DAABB& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_AABB_Point(const Collision2DAABB& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result); // untested

// Circle
bool Collision2DResponse_Circle_Circle(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_Circle_CapsuleY(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_Circle_CapsuleX(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_Circle_ConvexHull(const Collision2DCircle& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result); // TODO
bool Collision2DResponse_Circle_Point(const Collision2DCircle& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result);

// CapsuleY
bool Collision2DResponse_CapsuleY_CapsuleY(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_CapsuleY_CapsuleX(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result); // TODO
bool Collision2DResponse_CapsuleY_ConvexHull(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result); // TODO
bool Collision2DResponse_CapsuleY_Point(const Collision2DCapsuleY& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result); // untested

// CapsuleX
bool Collision2DResponse_CapsuleX_CapsuleX(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos, Collision2DResult& result);
bool Collision2DResponse_CapsuleX_ConvexHull(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos, Collision2DResult& result); // TODO
bool Collision2DResponse_CapsuleX_Point(const Collision2DCapsuleX& a, const MthVector2& apos, const MthVector2& b, Collision2DResult& result); // untested

// Hull
bool Collision2DResponse_ConvexHull_ConvexHull(Collision2DConvexHull& a, MthVector2& apos, Collision2DConvexHull& b, MthVector2& bpos, Collision2DResult& result);

// convenience function that will automatically call the correct function above
bool Collision2DResponse(const Collision2DShape& a, const MthVector2& apos, const Collision2DShape&b, const MthVector2& bpos, Collision2DResult& result);

#endif