#ifndef _MTHMATRIXROWMAJOR_H_
#define _MTHMATRIXROWMAJOR_H_

class MthVector2;
class MthVector3;
class MthVector4;

class MthMatrixRowMajor
{
public:
    MthMatrixRowMajor() {};

	MthMatrixRowMajor(const float* m) : _11(m[0]), _12(m[1]), _13(m[2]), _14(m[3]),
								_21(m[4]), _22(m[5]), _23(m[6]), _24(m[7]),
								_31(m[8]), _32(m[9]), _33(m[10]), _34(m[11]),
								_41(m[12]), _42(m[13]), _43(m[14]), _44(m[15]) {};

	MthMatrixRowMajor(const MthMatrixRowMajor& m)
					  : _11(m._11), _12(m._12), _13(m._13), _14(m._14),
						_21(m._21), _22(m._22), _23(m._23), _24(m._24),
						_31(m._31), _32(m._32), _33(m._33), _34(m._34),
						_41(m._41), _42(m._42), _43(m._43), _44(m._44) {};

    MthMatrixRowMajor(float _11, float _12, float _13, float _14,
			  float _21, float _22, float _23, float _24,
    		  float _31, float _32, float _33, float _34,
   			  float _41, float _42, float _43, float _44 )
				: _11(_11), _12(_12), _13(_13), _14(_14),
				_21(_21), _22(_22), _23(_23), _24(_24),
				_31(_31), _32(_32), _33(_33), _34(_34),
				_41(_41), _42(_42), _43(_43), _44(_44) {};

    // casting
	operator float*() { return (float*)this; };
	operator const float*() const { return (const float*)this; };

    // assignment operators
	MthMatrixRowMajor& operator+=(const MthMatrixRowMajor& m)
	{
		_11 += m._11; _12 += m._12; _13 += m._13; _14 += m._14;
		_21 += m._21; _22 += m._22; _23 += m._23; _24 += m._24;
		_31 += m._31; _32 += m._32; _33 += m._33; _34 += m._34;
		_41 += m._41; _42 += m._42; _43 += m._43; _44 += m._44;
		return *this;
	};

    MthMatrixRowMajor& operator-=(const MthMatrixRowMajor& m)
	{
		_11 -= m._11; _12 -= m._12; _13 -= m._13; _14 -= m._14;
		_21 -= m._21; _22 -= m._22; _23 -= m._23; _24 -= m._24;
		_31 -= m._31; _32 -= m._32; _33 -= m._33; _34 -= m._34;
		_41 -= m._41; _42 -= m._42; _43 -= m._43; _44 -= m._44;
		return *this;
	};

    MthMatrixRowMajor& operator*=(const MthMatrixRowMajor& m)
	{
		MthMatrixRowMajor temp(*this);
		return Multiply(*this, temp, m);
	};

    MthMatrixRowMajor& operator*=(float v)
	{
		_11 *= v; _12 *= v; _13 *= v; _14 *= v;
		_21 *= v; _22 *= v; _23 *= v; _24 *= v;
		_31 *= v; _32 *= v; _33 *= v; _34 *= v;
		_41 *= v; _42 *= v; _43 *= v; _44 *= v;
		return *this;
	};

    MthMatrixRowMajor& operator/=(float v)
	{
		_11 /= v; _12 /= v; _13 /= v; _14 /= v;
		_21 /= v; _22 /= v; _23 /= v; _24 /= v;
		_31 /= v; _32 /= v; _33 /= v; _34 /= v;
		_41 /= v; _42 /= v; _43 /= v; _44 /= v;
		return *this;
	};

    // unary operators
	MthMatrixRowMajor operator+() const { return *this; };
	MthMatrixRowMajor operator-() const
	{
		return MthMatrixRowMajor(-_11, -_12, -_13, -_14,
						 -_21, -_22, -_23, -_24,
						 -_31, -_32, -_33, -_34,
						 -_41, -_42, -_43, -_44);
	};

    // binary operators
	MthMatrixRowMajor operator+(const MthMatrixRowMajor& m) const
	{
		return MthMatrixRowMajor(_11 + m._11, _12 + m._12, _13 + m._13, _14 + m._14,
						 _21 + m._21, _22 + m._22, _23 + m._23, _24 + m._24,
						 _31 + m._31, _32 + m._32, _33 + m._33, _34 + m._34,
						 _41 + m._41, _42 + m._42, _43 + m._43, _44 + m._44);
	};

    MthMatrixRowMajor operator-(const MthMatrixRowMajor& m) const
	{
		return MthMatrixRowMajor(_11 - m._11, _12 - m._12, _13 - m._13, _14 - m._14,
						 _21 - m._21, _22 - m._22, _23 - m._23, _24 - m._24,
						 _31 - m._31, _32 - m._32, _33 - m._33, _34 - m._34,
						 _41 - m._41, _42 - m._42, _43 - m._43, _44 - m._44);
	};

    MthMatrixRowMajor operator*(const MthMatrixRowMajor& m) const
	{
		MthMatrixRowMajor temp;
		return Multiply(temp, *this, m);
	};

    MthMatrixRowMajor operator*(float v) const
	{
		return MthMatrixRowMajor(_11 * v, _12 * v, _13 * v, _14 * v,
						 _21 * v, _22 * v, _23 * v, _24 * v,
						 _31 * v, _32 * v, _33 * v, _34 * v,
						 _41 * v, _42 * v, _43 * v, _44 * v);
	};

    MthMatrixRowMajor operator/(float v) const
	{
		return MthMatrixRowMajor(_11 * v, _12 * v, _13 * v, _14 * v,
						 _21 * v, _22 * v, _23 * v, _24 * v,
						 _31 * v, _32 * v, _33 * v, _34 * v,
						 _41 * v, _42 * v, _43 * v, _44 * v);
	};

	bool operator==(const MthMatrixRowMajor& m) const
	{
		return _11 == m._11 && _12 == m._12 && _13 == m._13 && _14 == m._14 &&
			   _21 == m._21 && _22 == m._22 && _23 == m._23 && _24 == m._24 &&
			   _31 == m._31 && _32 == m._32 && _33 == m._33 && _34 == m._34 &&
			   _41 == m._41 && _42 == m._42 && _43 == m._43 && _44 == m._44;
	};

	bool operator!=(const MthMatrixRowMajor& m) const
	{
		return _11 != m._11 || _12 != m._12 || _13 != m._13 || _14 != m._14 ||
			   _21 != m._21 || _22 != m._22 || _23 != m._23 || _24 != m._24 ||
			   _31 != m._31 || _32 != m._32 || _33 != m._33 || _34 != m._34 ||
			   _41 != m._41 || _42 != m._42 || _43 != m._43 || _44 != m._44;
	};
	 
	// general
	void Identity()
	{
		_11 = _22 = _33 = _44 = 1.0f;
		_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f;
	};

	static MthMatrixRowMajor CreateIdentity()
	{
		return MthMatrixRowMajor(1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									0.0f, 0.0f, 0.0f, 1.0f);
	};

	bool IsIdentity() const
	{
		return _11 == 1.0f && _12 == 0.0f && 0.0f && _14 == 0.0f &&
			   _21 == 0.0f && _22 == 1.0f && 0.0f && _24 == 0.0f &&
			   _31 == 0.0f && _32 == 0.0f && 1.0f && _34 == 0.0f &&
			   _41 == 0.0f && _42 == 0.0f && 0.0f && _44 == 1.0f;
	};

	static MthMatrixRowMajor& Multiply(MthMatrixRowMajor& out, const MthMatrixRowMajor& a, const MthMatrixRowMajor& b);

	MthMatrixRowMajor& Transpose(MthMatrixRowMajor& out, const MthMatrixRowMajor& m);

	MthMatrixRowMajor& Transpose();

	void Scaling(float x, float y, float z);

	void Scaling(const MthVector3& v);

	void Translation(float x, float y, float z);

	void Translation(const MthVector3& v);

	void RotationX(float angle);

	void RotationY(float angle);

	void RotationZ(float angle);

	void RotationAxis(const MthVector3& axis, float angle);

	void RotationYawPitchRoll(float yaw, float pitch, float roll);

	void LookAtLH(const MthVector3& eye, const MthVector3& at, const MthVector3& up);

	void LookAtRH(const MthVector3& eye, const MthVector3& at, const MthVector3& up);

	void PerspectiveFovLH(float fovy, float aspect, float zn, float zf);

	void PerspectiveFovRH(float fovy, float aspect, float zn, float zf);

	void PerspectiveLH(float w, float h, float zn, float zf);

	void PerspectiveRH(float w, float h, float zn, float zf);

	void OrthoLH(float w, float h, float zn, float zf);

	void OrthoRH(float w, float h, float zn, float zf);

	void OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf);

	void OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf);
	
	void Transform(MthVector2& out,const  MthVector2& in) const;

	void Transform(MthVector3& out, const MthVector3& in) const;

	void Transform(MthVector4& out, const MthVector4& in) const;
	
	void TransformNormal(MthVector2& out,const  MthVector2& in) const;

	void TransformNormal(MthVector3& out, const MthVector3& in) const;

	float Determinant() const;
	
	static bool Inverse(MthMatrixRowMajor& out, const MthMatrixRowMajor& in);
	bool Inverse(const MthMatrixRowMajor& in) { return Inverse(*this, in); };
	bool Inverse() { return Inverse(*this, *this); };
	
    union
	{
		struct
		{
			float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
		};
        float d[4][4];
    };
};

#endif