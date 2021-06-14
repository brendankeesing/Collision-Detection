#include "MthPlane.h"
#include <cmath>

void MthPlane::FromPoints(const MthVector3& p1, const MthVector3& p2, const MthVector3& p3)
{
	MthVector3 edge1 = p2 - p1;
	MthVector3 edge2 = p3 - p1;
	
	MthVector3 normal;
	normal.Cross(edge1, edge2);
	normal.Normalize();

	FromPointNormal(p1, normal);
}

void MthPlane::FromPointNormal(const MthVector3& point, const MthVector3& normal)
{
	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = -point.Dot(normal);
}

void MthPlane::Normalize(MthPlane& out, const MthPlane& p)
{
	float norm = sqrt(p.a * p.a + p.b * p.b + p.c * p.c);
	if (norm)
	{
		norm = 1.0f / norm;
		out.a = p.a * norm;
		out.b = p.b * norm;
		out.c = p.c * norm;
		out.d = p.d * norm;
	}
	else
	{
		out.a = 0.0f;
		out.b = 0.0f;
		out.c = 0.0f;
		out.d = 0.0f;
	}
}

float MthPlane::Dot(const MthVector4& v) const
{
	return a * v.x + b * v.y + c * v.z + d * v.w;
}

bool MthPlane::LineIntersect(MthVector3& out, const MthVector3& p1, const MthVector3& p2) const
{
	MthVector3 direction = p2 - p1;
	MthVector3 normal(a, b, c);
	float dot = normal.Dot(direction);

	// if no intersection
	if (!dot)
		return false;

	float temp = (d + normal.Dot(p1)) / dot;
	out.x = p1.x - temp * direction.x;
	out.y = p1.y - temp * direction.y;
	out.z = p1.z - temp * direction.z;
	return true;
}
