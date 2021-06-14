#ifndef _MTHVECTOR_H_
#define _MTHVECTOR_H_

#include <cmath>

class MthVector2
{
public:
    MthVector2() : x(0), y(0) {};
	MthVector2(const float* v) : x(v[0]), y(v[1]) {};
    MthVector2(float x, float y) : x(x), y(y) {};

    // casting
	operator float*() { return (float*)this; };
	operator const float*() const { return (const float*)this; };

    // assignment operators
	MthVector2& operator+=(const MthVector2& v) { x += v.x; y += v.y; return *this; };
    MthVector2& operator-=(const MthVector2& v) { x -= v.x; y -= v.y; return *this; };
    MthVector2& operator*=(float v) { x *= v; y *= v; return *this; };
    MthVector2& operator/=(float v) { x /= v; y /= v; return *this; };

    // unary operators
	MthVector2 operator+() const { return *this; };
	MthVector2 operator-() const { return MthVector2(-x, -y); };

    // binary operators
	MthVector2 operator+(const MthVector2& v) const { return MthVector2(x + v.x, y + v.y); };
    MthVector2 operator-(const MthVector2& v) const { return MthVector2(x - v.x, y - v.y); };
    MthVector2 operator*(float v) const { return MthVector2(x * v, y * v); };
    MthVector2 operator/(float v) const { return MthVector2(x / v, y / v); };

	bool operator==(const MthVector2& v) const { return x == v.x && y == v.y; };
	bool operator!=(const MthVector2& v) const { return x != v.x || y != v.y; };

	// general
	float Length() const { return sqrt(x * x + y * y); };
	float LengthSqr() const { return x * x + y * y; };
	static float Distance(MthVector2& a, MthVector2& b) { return (a - b).Length(); };
	void Normalize() { *this /= Length(); };
	static MthVector2 Normalize(const MthVector2& v) { return v / v.Length(); };
	static MthVector2& Normalize(MthVector2& out, const MthVector2& v) { return out = v / v.Length(); };
	float Dot(const MthVector2& v) const { return x * v.x + y * v.y; };
	static float Dot(const MthVector2& a, const MthVector2& b) { return a.x * b.x + a.y * b.y; };

	static MthVector2& Lerp(MthVector2& out, const MthVector2& a, const MthVector2& b, float s);

	void Lerp(const MthVector2& a, const MthVector2& b, float s);

	union
	{
		struct
		{
			float x, y;
		};
		float d[2];
	};
};

class MthVector3
{
public:
    MthVector3() : x(0), y(0), z(0) {};
	MthVector3(const float* v) : x(v[0]), y(v[1]), z(v[2]) {};
    MthVector3(float x, float y, float z) : x(x), y(y), z(z) {};

    // casting
	operator float*() { return (float*)this; };
	operator const float*() const { return (const float*)this; };

    // assignment operators
	MthVector3& operator+=(const MthVector3& v) { x += v.x; y += v.y; z += v.z; return *this; };
    MthVector3& operator-=(const MthVector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; };
    MthVector3& operator*=(float v) { x *= v; y *= v; z *= v; return *this; };
    MthVector3& operator/=(float v) { x /= v; y /= v; z /= v; return *this; };

    // unary operators
	MthVector3 operator+() const { return *this; };
	MthVector3 operator-() const { return MthVector3(-x, -y, -z); };

    // binary operators
	MthVector3 operator+(const MthVector3& v) const { return MthVector3(x + v.x, y + v.y, z + v.z); };
    MthVector3 operator-(const MthVector3& v) const { return MthVector3(x - v.x, y - v.y, z - v.z); };
    MthVector3 operator*(float v) const { return MthVector3(x * v, y * v, z * v); };
    MthVector3 operator/(float v) const { return MthVector3(x / v, y / v, z / v); };

	bool operator==(const MthVector3& v) const { return x == v.x && y == v.y && z == v.z; };
	bool operator!=(const MthVector3& v) const { return x != v.x || y != v.y || z != v.z; };
	
	// general
	float Length() const { return sqrt(x * x + y * y + z * z); };
	float LengthSqr() const { return x * x + y * y + z * z; };
	static float Distance(MthVector3& a, MthVector3& b) { return (a - b).Length(); };
	MthVector3& Normalize() { return *this /= Length(); };
	static MthVector3 Normalize(const MthVector3& v) { return v / v.Length(); };
	static MthVector3& Normalize(MthVector3& out, const MthVector3& v) { return out = v / v.Length(); };
	float Dot(const MthVector3& v) const { return x * v.x + y * v.y + z * v.z; };
	static float Dot(const MthVector3& a, const MthVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; };

	static MthVector3& Cross(MthVector3& out, const MthVector3& a, const MthVector3& b);

	void Cross(const MthVector3& a, const MthVector3& b);

	void Cross(const MthVector3& v);

	static MthVector3& Lerp(MthVector3& out, const MthVector3& a, const MthVector3& b, float s);

	void Lerp(const MthVector3& a, const MthVector3& b, float s);

	union
	{
		struct
		{
			float x, y, z;
		};
		float d[3];
	};
};

class MthVector4
{
public:
    MthVector4() : x(0), y(0), z(0), w(0) {};
	MthVector4(const float* v) : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {};
    MthVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

    // casting
	operator float*() { return (float*)this; };
	operator const float*() const { return (const float*)this; };

    // assignment operators
	MthVector4& operator+=(const MthVector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; };
    MthVector4& operator-=(const MthVector4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; };
    MthVector4& operator*=(float v) { x *= v; y *= v; z *= v; w *= v; return *this; };
    MthVector4& operator/=(float v) { x /= v; y /= v; z /= v; w /= v; return *this; };

    // unary operators
	MthVector4 operator+() const { return *this; };
	MthVector4 operator-() const { return MthVector4(-x, -y, -z, -w); };

    // binary operators
	MthVector4 operator+(const MthVector4& v) const { return MthVector4(x + v.x, y + v.y, z + v.z, w + v.w); };
    MthVector4 operator-(const MthVector4& v) const { return MthVector4(x - v.x, y - v.y, z - v.z, w - v.w); };
    MthVector4 operator*(float v) const { return MthVector4(x * v, y * v, z * v, w * v); };
    MthVector4 operator/(float v) const { return MthVector4(x / v, y / v, z / v, w / v); };

	bool operator==(const MthVector4& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; };
	bool operator!=(const MthVector4& v) const { return x != v.x || y != v.y || z != v.z || w != v.w; };
	
	// general
	float Length() const { return sqrt(x * x + y * y + z * z + w * w); };
	float LengthSqr() const { return x * x + y * y + z * z + w * w; };
	static float Distance(MthVector4& a, MthVector4& b) { return (a - b).Length(); };
	void Normalize() { *this /= Length(); };
	static MthVector4 Normalize(const MthVector4& v) { return v / v.Length(); };
	static MthVector4& Normalize(MthVector4& out, const MthVector4& v) { return out = v / v.Length(); };
	float Dot(const MthVector4& v) const { return x * v.x + y * v.y + z * v.z + w * v.w; };
	static float Dot(const MthVector4& a, const MthVector4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; };

	static MthVector4& Lerp(MthVector4& out, const MthVector4& a, const MthVector4& b, float s);

	void Lerp(const MthVector4& a, const MthVector4& b, float s);

	void Cross(const MthVector4& a, const MthVector4& b, const MthVector4& c);

	union
	{
		struct
		{
			float x, y, z, w;
		};
		float d[4];
	};
};

#endif
