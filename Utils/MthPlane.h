#ifndef _MTHPLANE_H_
#define _MTHPLANE_H_

#include "Math.h"

class MthPlane
{
public:
    MthPlane() {};
	MthPlane(const float* v) : a(v[0]), b(v[1]), c(v[2]), d(v[3]) {};
    MthPlane(float a, float b, float c, float d) : a(a), b(b), c(c), d(d) {};
	MthPlane(const MthVector3& p1, const MthVector3& p2, const MthVector3& p3) { FromPoints(p1, p2, p3); };
	MthPlane(const MthVector3& point, const MthVector3& normal) { FromPointNormal(point, normal); };

    // casting
	operator float*() { return (float*)this; };
	operator const float*() const { return (const float*)this; };

    // assignment operators
    MthPlane& operator*=(float v) { a *= v; b *= v; c *= v; d *= v; return *this; };
    MthPlane& operator/=(float v) { a /= v; b /= v; c /= v; d /= v; return *this; };

    // unary operators
	MthPlane operator+() const { return *this; };
	MthPlane operator-() const { return MthPlane(-a, -b, -c, -d); };

	bool operator==(const MthPlane& v) const { return a == v.a && b == v.b && c == v.c && d == v.d; };
	bool operator!=(const MthPlane& v) const { return a != v.a || b != v.b || c != v.c || d != v.d; };
	
	// general
	void FromPoints(const MthVector3& p1, const MthVector3& p2, const MthVector3& p3);
	void FromPointNormal(const MthVector3& point, const MthVector3& normal);
	void Normalize() { Normalize(*this, *this); };
	static void Normalize(MthPlane& out, const MthPlane& p);
	float Dot(const MthVector4& v) const;
	bool LineIntersect(MthVector3& out, const MthVector3& p1, const MthVector3& p2) const;

	union
	{
		struct
		{
			float a, b, c, d;
		};
		float m[4];
	};
};

#endif