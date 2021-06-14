#ifndef _COLLISIONFRUSTUM_H_
#define _COLLISIONFRUSTUM_H_

#include "../Utils/Math.h"

class CollisionFrustum
{
public:
	// Retrieves the center point of the frustum.
	void GetCenterPoint(MthVector3& out) const;

	// Gets the distance from the specified point to the furthest point in the frustum.
	// Passing the value from GetCenterPoint() into this will get you the radius.
	float GetFurthestDistance(const MthVector3& point) const;

	// returns array of 8 vectors corresponding the corner points of the frustum
	const MthVector3* GetVertices() const { return _vertices; };

	bool IntersectAABB(const MthVector3& p, const MthVector3& dimensions) const;
	
	bool IntersectPoint(const MthVector3& p) const;

	bool IntersectSphere(const MthVector3& p, float radius) const;

	void Recalculate(const MthMatrix& viewprojection);

private:
	void _calculatefromvertices();

	MthVector3 _vertices[8];
	MthPlane _planes[6];
};

#endif