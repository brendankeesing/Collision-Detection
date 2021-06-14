#ifndef _COLLISION2D_CHECK_H_
#define _COLLISION2D_CHECK_H_

#include "Collision2DTypes.h"

// return true on collision

// AABB
bool Collision2DCheck_AABB_AABB(const Collision2DAABB& a, const MthVector2& apos, const Collision2DAABB& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_Circle(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_CapsuleY(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_CapsuleX(const Collision2DAABB& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_ConvexHull(const Collision2DAABB& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_Ray(const Collision2DAABB& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);
bool Collision2DCheck_AABB_Point(const Collision2DAABB& a, const MthVector2& apos, const MthVector2& b); // untested

// Circle
bool Collision2DCheck_Circle_Circle(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCircle& b, const MthVector2& bpos);
bool Collision2DCheck_Circle_CapsuleY(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos);
bool Collision2DCheck_Circle_CapsuleX(const Collision2DCircle& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos);
bool Collision2DCheck_Circle_ConvexHull(const Collision2DCircle& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos); // a tiny bit buggy on corners
bool Collision2DCheck_Circle_Ray(const Collision2DCircle& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);
bool Collision2DCheck_Circle_Point(const Collision2DCircle& a, const MthVector2& apos, const MthVector2& b); // untested

// CapsuleY
bool Collision2DCheck_CapsuleY_CapsuleY(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleY& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleY_CapsuleX(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleY_ConvexHull(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleY_Ray(const Collision2DCapsuleY& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleY_Point(const Collision2DCapsuleY& a, const MthVector2& apos, const MthVector2& b); // untested

// CapsuleX
bool Collision2DCheck_CapsuleX_CapsuleX(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DCapsuleX& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleX_ConvexHull(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleX_Ray(const Collision2DCapsuleX& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);
bool Collision2DCheck_CapsuleX_Point(const Collision2DCapsuleX& a, const MthVector2& apos, const MthVector2& b); // untested

// Hull
bool Collision2DCheck_ConvexHull_ConvexHull(const Collision2DConvexHull& a, const MthVector2& apos, const Collision2DConvexHull& b, const MthVector2& bpos);
bool Collision2DCheck_ConvexHull_Ray(const Collision2DConvexHull& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);
bool Collision2DCheck_ConvexHull_Point(const Collision2DConvexHull& a, const MthVector2& apos, const MthVector2& b); // untested

// Ray
bool Collision2DCheck_Ray_Ray(const Collision2DRay& a, const MthVector2& apos, const Collision2DRay& b, const MthVector2& bpos);

// convenience function that will automatically call the correct function above
bool Collision2DCheck(const Collision2DShape& a, const MthVector2& apos, const Collision2DShape&b, const MthVector2& bpos);

// convenience function that will automatically call the correct function above for points
bool Collision2DCheck(const Collision2DShape& a, const MthVector2& apos, const MthVector2& bpos);

#endif