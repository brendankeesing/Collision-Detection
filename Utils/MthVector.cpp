#include "MthVector.h"
#include <cmath>

// MthVector2

MthVector2& MthVector2::Lerp(MthVector2& out, const MthVector2& a, const MthVector2& b, float s)
{
	out.x = a.x + s * (b.x - a.x);
	out.y = a.y + s * (b.y - a.y);
	return out;
};

void MthVector2::Lerp(const MthVector2& a, const MthVector2& b, float s)
{
	x = a.x + s * (b.x - a.x);
	y = a.y + s * (b.y - a.y);
};

// MthVector3

MthVector3& MthVector3::Cross(MthVector3& out, const MthVector3& a, const MthVector3& b)
{
	out.x = a.y * b.z - a.z * b.y;
	out.y = a.z * b.x - a.x * b.z;
	out.z = a.x * b.y - a.y * b.x;
	return out;
};

void MthVector3::Cross(const MthVector3& a, const MthVector3& b)
{
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
};

void MthVector3::Cross(const MthVector3& v)
{
	float oldx = x;
	float oldy = y;
	x = y * v.z - z * v.y;
	y = z * v.x - oldx * v.z;
	z = oldx * v.y - oldy * v.x;
};

MthVector3& MthVector3::Lerp(MthVector3& out, const MthVector3& a, const MthVector3& b, float s)
{
	out.x = a.x + s * (b.x - a.x);
	out.y = a.y + s * (b.y - a.y);
	out.z = a.z + s * (b.z - a.z);
	return out;
};

void MthVector3::Lerp(const MthVector3& a, const MthVector3& b, float s)
{
	x = a.x + s * (b.x - a.x);
	y = a.y + s * (b.y - a.y);
	z = a.z + s * (b.z - a.z);
};

// MthVector4

MthVector4& MthVector4::Lerp(MthVector4& out, const MthVector4& a, const MthVector4& b, float s)
{
	out.x = a.x + s * (b.x - a.x);
	out.y = a.y + s * (b.y - a.y);
	out.z = a.z + s * (b.z - a.z);
	out.w = a.w + s * (b.w - a.w);
	return out;
};

void MthVector4::Lerp(const MthVector4& a, const MthVector4& b, float s)
{
	x = a.x + s * (b.x - a.x);
	y = a.y + s * (b.y - a.y);
	z = a.z + s * (b.z - a.z);
	w = a.w + s * (b.w - a.w);
};

void MthVector4::Cross(const MthVector4& a, const MthVector4& b, const MthVector4& c)//
{
	x = a.y * (b.z * c.w - c.z * b.w) - a.z * (b.y * c.w - c.y * b.w) + a.w * (b.y * c.z - b.z *c.y);
	y = -(a.x * (b.z * c.w - c.z * b.w) - a.z * (b.x * c.w - c.x * b.w) + a.w * (b.x * c.z - c.x * b.z));
	z = a.x * (b.y * c.w - c.y * b.w) - a.y * (b.x *c.w - c.x * b.w) + a.w * (b.x * c.y - c.x * b.y);
	w = -(a.x * (b.y * c.z - c.y * b.z) - a.y * (b.x * c.z - c.x *b.z) + a.z * (b.x * c.y - c.x * b.y));
}