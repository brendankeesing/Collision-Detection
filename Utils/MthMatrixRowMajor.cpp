#include "MthMatrixRowMajor.h"
#include "MthVector.h"

MthMatrixRowMajor& MthMatrixRowMajor::Multiply(MthMatrixRowMajor& out, const MthMatrixRowMajor& a, const MthMatrixRowMajor& b)
{
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			out.d[i][j] = a.d[i][0] * b.d[0][j] + a.d[i][1] * b.d[1][j] + a.d[i][2] * b.d[2][j] + a.d[i][3] * b.d[3][j];
	}
	return out;
};

MthMatrixRowMajor& MthMatrixRowMajor::Transpose(MthMatrixRowMajor& out, const MthMatrixRowMajor& m)
{
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			out.d[i][j] = m.d[j][i];
	}
	return out;
};

MthMatrixRowMajor& MthMatrixRowMajor::Transpose()
{
	MthMatrixRowMajor temp(*this);
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			d[i][j] = temp.d[j][i];
	}
	return *this;
};

void MthMatrixRowMajor::Scaling(float x, float y, float z)
{
	_11 = x;
	_22 = y;
	_33 = z;
	_44 = 1.0f;
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f;
};

void MthMatrixRowMajor::Scaling(const MthVector3& v)
{
	Scaling(v.x, v.y, v.z);
};

void MthMatrixRowMajor::Translation(float x, float y, float z)
{
	_41 = x;
	_42 = y;
	_43 = z;
	_11 = _22 = _33 = _44 = 1.0f;
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = 0.0f;
};

void MthMatrixRowMajor::Translation(const MthVector3& v)
{
	Translation(v.x, v.y, v.z);
};

void MthMatrixRowMajor::RotationX(float angle)
{
	Identity();
	_22 = _33 = cos(angle);
	_32 = -(_23 = sin(angle));
};

void MthMatrixRowMajor::RotationY(float angle)
{
	Identity();
	_11 = _33 = cos(angle);
	_13 = -(_31 = sin(angle));
};

void MthMatrixRowMajor::RotationZ(float angle)
{
	Identity();
	_11 = _22 = cos(angle);
	_21 = -(_12 = sin(angle));
};

void MthMatrixRowMajor::RotationAxis(const MthVector3& axis, float angle)
{
	MthVector3 v;
	MthVector3::Normalize(v, axis);

	float cosangle = cos(angle);
	float sinangle = sin(angle);
	float mcosangle =  1.0f - cosangle;

	Identity();
	_11 = mcosangle * v.x * v.x + cosangle;
	_21 = mcosangle * v.x * v.y - sinangle * v.z;
	_31 = mcosangle * v.x * v.z + sinangle * v.y;
	_12 = mcosangle * v.y * v.x + sinangle * v.z;
	_22 = mcosangle * v.y * v.y + cosangle;
	_32 = mcosangle * v.y * v.z - sinangle * v.x;
	_13 = mcosangle * v.z * v.x - sinangle * v.y;
	_23 = mcosangle * v.z * v.y + sinangle * v.x;
	_33 = mcosangle * v.z * v.z + cosangle;
};

void MthMatrixRowMajor::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
	MthMatrixRowMajor temp;
	RotationZ(roll);
	temp.RotationX(pitch);
	*this *= temp;
	temp.RotationY(yaw);
	*this *= temp;
};

void MthMatrixRowMajor::LookAtLH(const MthVector3& eye, const MthVector3& at, const MthVector3& up)
{
	MthVector3 zaxis = (at - eye).Normalize();
	MthVector3 xaxis, yaxis;
	xaxis.Cross(up, zaxis);
	xaxis.Normalize();
	yaxis.Cross(zaxis, xaxis);
		
	_11 = xaxis.x;
	_12 = yaxis.x;
	_13 = zaxis.x;
	_14 = 0.0f;

	_21 = xaxis.y;
	_22 = yaxis.y;
	_23 = zaxis.y;
	_24 = 0.0f;

	_31 = xaxis.z;
	_32 = yaxis.z;
	_33 = zaxis.z;
	_34 = 0.0f;

	_41 = -MthVector3::Dot(xaxis, eye);
	_42 = -MthVector3::Dot(yaxis, eye);
	_43 = -MthVector3::Dot(zaxis, eye);
	_44 = 1.0f;
};

void MthMatrixRowMajor::LookAtRH(const MthVector3& eye, const MthVector3& at, const MthVector3& up)
{
	MthVector3 zaxis = (eye - at).Normalize();
	MthVector3 xaxis, yaxis;
	xaxis.Cross(up, zaxis);
	xaxis.Normalize();
	yaxis.Cross(zaxis, xaxis);
		
	_11 = xaxis.x;
	_12 = yaxis.x;
	_13 = zaxis.x;
	_14 = 0.0f;

	_21 = xaxis.y;
	_22 = yaxis.y;
	_23 = zaxis.y;
	_24 = 0.0f;

	_31 = xaxis.z;
	_32 = yaxis.z;
	_33 = zaxis.z;
	_34 = 0.0f;

	_41 = -MthVector3::Dot(xaxis, eye);
	_42 = -MthVector3::Dot(yaxis, eye);
	_43 = -MthVector3::Dot(zaxis, eye);
	_44 = 1.0f;
};

void MthMatrixRowMajor::PerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_34 = 1.0f;

	_22 = 1.0f / tan(fovy / 2);
	_11 = _22 / aspect;
	_33 = zf / (zf - zn);
	_43 = -zn * _33;
};

void MthMatrixRowMajor::PerspectiveFovRH(float fovy, float aspect, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_34 = -1.0f;
	
	_22 = 1.0f / tan(fovy / 2);
	_11 = _22 / aspect;
	_33 = zf / (zn - zf);
	_43 = zn * _33;
};

void MthMatrixRowMajor::PerspectiveLH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_34 = 1.0f;

	_11 = 2.0f * zn / w;
	_22 = 2.0f * zn / h;
	_33 = zf / (zf - zn);
	_43 = zn * _33;
};

void MthMatrixRowMajor::PerspectiveRH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_34 = -1.0f;

	_11 = 2.0f * zn / w;
	_22 = 2.0f * zn / h;
	_33 = zf / (zn - zf);
	_43 = zn * _33;
};

void MthMatrixRowMajor::OrthoLH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / w;
	_22 = 2.0f / h;
	_33 = 1.0f / (zf - zn);
	_43 = zn / (zn - zf);
};

void MthMatrixRowMajor::OrthoRH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / w;
	_22 = 2.0f / h;
	_33 = 1.0f / (zn - zf);
	_43 = zn / (zn - zf);
};

void MthMatrixRowMajor::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / (r - l);
	_22 = 2.0f / (t - b);
	_33 = 1.0f / (zf - zn);
	_41 = (l + r) / (l - r);
	_42 = (t + b) / (b - t);
	_43 = zn / (zn - zf);
};

void MthMatrixRowMajor::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / (r - l);
	_22 = 2.0f / (t - b);
	_33 = 1.0f / (zf - zn);
	_41 = (l + r) / (l - r);
	_42 = (t + b) / (b - t);
	_43 = zn / (zf - zn);
};

void MthMatrixRowMajor::Transform(MthVector2& out, const MthVector2& in) const
{
	MthVector2 temp(in);
	out.x = _11 * temp.x + _21 * temp.y + _41;
	out.y = _12 * temp.x + _22 * temp.y + _42;
}

void MthMatrixRowMajor::Transform(MthVector3& out, const MthVector3& in) const
{
	MthVector3 temp(in);
	out.x = _11 * temp.x + _21 * temp.y + _31 * temp.z + _41;
	out.y = _12 * temp.x + _22 * temp.y + _32 * temp.z + _42;
	out.z = _13 * temp.x + _23 * temp.y + _33 * temp.z + _43;
}

void MthMatrixRowMajor::Transform(MthVector4& out, const MthVector4& in) const
{
	MthVector4 temp(in);
	out.x = _11 * temp.x + _21 * temp.y + _31 * temp.z + _41 * temp.w;
	out.y = _12 * temp.x + _22 * temp.y + _32 * temp.z + _42 * temp.w;
	out.z = _13 * temp.x + _23 * temp.y + _33 * temp.z + _43 * temp.w;
	out.w = _14 * temp.x + _24 * temp.y + _34 * temp.z + _44 * temp.w;
}

void MthMatrixRowMajor::TransformNormal(MthVector2& out, const MthVector2& in) const
{
	MthVector2 temp(in);
	out.x = _11 * temp.x + _21 * temp.y;
	out.y = _12 * temp.x + _22 * temp.y;
}

void MthMatrixRowMajor::TransformNormal(MthVector3& out, const MthVector3& in) const
{
	MthVector3 temp(in);
	out.x = _11 * temp.x + _21 * temp.y + _31 * temp.z;
	out.y = _12 * temp.x + _22 * temp.y + _32 * temp.z;
	out.z = _13 * temp.x + _23 * temp.y + _33 * temp.z;
}

float MthMatrixRowMajor::Determinant() const
{
	MthVector4 v1(_11, _21, _31, _41);
	MthVector4 v2(_12, _22, _32, _42);
	MthVector4 v3(_13, _23, _33, _43);

	MthVector4 minor;
	minor.Cross(v1, v2, v3);
	return -(_14 * minor.x + _24 * minor.y + _34 * minor.z + _44 * minor.w);
}

bool MthMatrixRowMajor::Inverse(MthMatrixRowMajor& out, const MthMatrixRowMajor& in)
{
	float det = in.Determinant();
	if (det == 0.0f)
		return false;

	MthVector4 v, vec[3];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j != i )
			{
				int a = j;
				if (j > i)
					--a;

				vec[a].x = in.d[j][0];
				vec[a].y = in.d[j][1];
				vec[a].z = in.d[j][2];
				vec[a].w = in.d[j][3];
			}
		}

		v.Cross(vec[0], vec[1], vec[2]);

		for (int j = 0; j < 4; j++)
			out.d[j][i] = pow(-1.0f, i) * v[j] / det;
	}
	return true;
}