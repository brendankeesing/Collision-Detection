#include "MthMatrixColumnMajor.h"
#include "MthVector.h"

MthMatrixColumnMajor& MthMatrixColumnMajor::Multiply(MthMatrixColumnMajor& out, const MthMatrixColumnMajor& a, const MthMatrixColumnMajor& b)
{
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			out.d[j][i] = a.d[0][i] * b.d[j][0] + a.d[1][i] * b.d[j][1] + a.d[2][i] * b.d[j][2] + a.d[3][i] * b.d[j][3];
	}
	return out;
};

MthMatrixColumnMajor& MthMatrixColumnMajor::Transpose(MthMatrixColumnMajor& out, const MthMatrixColumnMajor& m)
{
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			out.d[i][j] = m.d[j][i];
	}
	return out;
};

MthMatrixColumnMajor& MthMatrixColumnMajor::Transpose()
{
	MthMatrixColumnMajor temp(*this);
	int j;
	for (int i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
			d[i][j] = temp.d[j][i];
	}
	return *this;
};

void MthMatrixColumnMajor::Scaling(float x, float y, float z)
{
	_11 = x;
	_22 = y;
	_33 = z;
	_44 = 1.0f;
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f;
};

void MthMatrixColumnMajor::Scaling(const MthVector3& v)
{
	Scaling(v.x, v.y, v.z);
};

void MthMatrixColumnMajor::Translation(float x, float y, float z)
{
	_14 = x;
	_24 = y;
	_34 = z;
	_11 = _22 = _33 = _44 = 1.0f;
	_12 = _13 = _21 = _23 = _31 = _32 = _41 = _42 = _43 = 0.0f;
};

void MthMatrixColumnMajor::Translation(const MthVector3& v)
{
	Translation(v.x, v.y, v.z);
};

void MthMatrixColumnMajor::RotationX(float angle)
{
	Identity();
	_22 = _33 = cos(angle);
	_23 = -(_32 = sin(angle));
};

void MthMatrixColumnMajor::RotationY(float angle)
{
	Identity();
	_11 = _33 = cos(angle);
	_31 = -(_13 = sin(angle));
};

void MthMatrixColumnMajor::RotationZ(float angle)
{
	Identity();
	_11 = _22 = cos(angle);
	_12 = -(_21 = sin(angle));
};

void MthMatrixColumnMajor::RotationAxis(const MthVector3& axis, float angle)
{
	MthVector3 v;
	MthVector3::Normalize(v, axis);

	float cosangle = cos(angle);
	float sinangle = sin(angle);
	float mcosangle =  1.0f - cosangle;

	Identity();
	_11 = mcosangle * v.x * v.x + cosangle;
	_12 = mcosangle * v.x * v.y - sinangle * v.z;
	_13 = mcosangle * v.x * v.z + sinangle * v.y;
	_21 = mcosangle * v.y * v.x + sinangle * v.z;
	_22 = mcosangle * v.y * v.y + cosangle;
	_23 = mcosangle * v.y * v.z - sinangle * v.x;
	_31 = mcosangle * v.z * v.x - sinangle * v.y;
	_32 = mcosangle * v.z * v.y + sinangle * v.x;
	_33 = mcosangle * v.z * v.z + cosangle;
};

void MthMatrixColumnMajor::RotationYawPitchRoll(float yaw, float pitch, float roll)
{
	MthMatrixColumnMajor temp;
	RotationZ(roll);
	temp.RotationX(pitch);
	*this *= temp;
	temp.RotationY(yaw);
	*this *= temp;
};

void MthMatrixColumnMajor::LookAtLH(const MthVector3& eye, const MthVector3& at, const MthVector3& up)
{
	MthVector3 zaxis = (at - eye).Normalize();
	MthVector3 xaxis, yaxis;
	xaxis.Cross(up, zaxis);
	xaxis.Normalize();
	yaxis.Cross(zaxis, xaxis);
		
	_11 = xaxis.x;
	_21 = yaxis.x;
	_31 = zaxis.x;
	_41 = 0.0f;

	_12 = xaxis.y;
	_22 = yaxis.y;
	_32 = zaxis.y;
	_42 = 0.0f;

	_13 = xaxis.z;
	_23 = yaxis.z;
	_33 = zaxis.z;
	_43 = 0.0f;

	_14 = -MthVector3::Dot(xaxis, eye);
	_24 = -MthVector3::Dot(yaxis, eye);
	_34 = -MthVector3::Dot(zaxis, eye);
	_44 = 1.0f;
};

void MthMatrixColumnMajor::LookAtRH(const MthVector3& eye, const MthVector3& at, const MthVector3& up)
{
	MthVector3 zaxis = (eye - at).Normalize();
	MthVector3 xaxis, yaxis;
	xaxis.Cross(up, zaxis);
	xaxis.Normalize();
	yaxis.Cross(zaxis, xaxis);
		
	_11 = xaxis.x;
	_21 = yaxis.x;
	_31 = zaxis.x;
	_41 = 0.0f;

	_12 = xaxis.y;
	_22 = yaxis.y;
	_32 = zaxis.y;
	_42 = 0.0f;

	_13 = xaxis.z;
	_23 = yaxis.z;
	_33 = zaxis.z;
	_43 = 0.0f;

	_14 = -MthVector3::Dot(xaxis, eye);
	_24 = -MthVector3::Dot(yaxis, eye);
	_34 = -MthVector3::Dot(zaxis, eye);
	_44 = 1.0f;
};

void MthMatrixColumnMajor::PerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_43 = 1.0f;

	_22 = 1.0f / tan(fovy / 2);
	_11 = _22 / aspect;
	_33 = zf / (zf - zn);
	_34 = -zn * _33;
};

void MthMatrixColumnMajor::PerspectiveFovRH(float fovy, float aspect, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_43 = -1.0f;
	
	_22 = 1.0f / tan(fovy / 2);
	_11 = _22 / aspect;
	_33 = zf / (zn - zf);
	_34 = zn * _33;
};

void MthMatrixColumnMajor::PerspectiveLH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_43 = 1.0f;

	_11 = 2.0f * zn / w;
	_22 = 2.0f * zn / h;
	_33 = zf / (zf - zn);
	_34 = zn * _33;
};

void MthMatrixColumnMajor::PerspectiveRH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _44 = 0.0f;
	_43 = -1.0f;

	_11 = 2.0f * zn / w;
	_22 = 2.0f * zn / h;
	_33 = zf / (zn - zf);
	_34 = zn * _33;
};

void MthMatrixColumnMajor::OrthoLH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _43 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / w;
	_22 = 2.0f / h;
	_33 = 1.0f / (zf - zn);
	_34 = zn / (zn - zf);
};

void MthMatrixColumnMajor::OrthoRH(float w, float h, float zn, float zf)
{
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _41 = _42 = _43 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / w;
	_22 = 2.0f / h;
	_33 = 1.0f / (zn - zf);
	_34 = zn / (zn - zf);
};

void MthMatrixColumnMajor::OrthoOffCenterLH(float l, float r, float b, float t, float zn, float zf)
{
	_12 = _13 = _41 = _21 = _23 = _42 = _31 = _32 = _43 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / (r - l);
	_22 = 2.0f / (t - b);
	_33 = 1.0f / (zf - zn);
	_14 = (l + r) / (l - r);
	_24 = (t + b) / (b - t);
	_34 = zn / (zn - zf);
};

void MthMatrixColumnMajor::OrthoOffCenterRH(float l, float r, float b, float t, float zn, float zf)
{
	_12 = _13 = _41 = _21 = _23 = _42 = _31 = _32 = _43 = 0.0f;
	_44 = 1.0f;

	_11 = 2.0f / (r - l);
	_22 = 2.0f / (t - b);
	_33 = 1.0f / (zf - zn);
	_14 = (l + r) / (l - r);
	_24 = (t + b) / (b - t);
	_34 = zn / (zf - zn);
};

void MthMatrixColumnMajor::Transform(MthVector2& out, const MthVector2& in) const
{
	MthVector2 temp(in);
	out.x = _11 * temp.x + _12 * temp.y + _14;
	out.y = _21 * temp.x + _22 * temp.y + _24;
}

void MthMatrixColumnMajor::Transform(MthVector3& out, const MthVector3& in) const
{
	MthVector3 temp(in);
	out.x = _11 * temp.x + _12 * temp.y + _13 * temp.z + _14;
	out.y = _21 * temp.x + _22 * temp.y + _23 * temp.z + _24;
	out.z = _31 * temp.x + _32 * temp.y + _33 * temp.z + _34;
}

void MthMatrixColumnMajor::Transform(MthVector4& out, const MthVector4& in) const
{
	MthVector4 temp(in);
	out.x = _11 * temp.x + _12 * temp.y + _13 * temp.z + _14 * temp.w;
	out.y = _21 * temp.x + _22 * temp.y + _23 * temp.z + _24 * temp.w;
	out.z = _31 * temp.x + _32 * temp.y + _33 * temp.z + _34 * temp.w;
	out.w = _41 * temp.x + _42 * temp.y + _43 * temp.z + _44 * temp.w;
}

void MthMatrixColumnMajor::TransformNormal(MthVector2& out, const MthVector2& in) const
{
	MthVector2 temp(in);
	out.x = _11 * temp.x + _12 * temp.y;
	out.y = _21 * temp.x + _22 * temp.y;
}

void MthMatrixColumnMajor::TransformNormal(MthVector3& out, const MthVector3& in) const
{
	MthVector3 temp(in);
	out.x = _11 * temp.x + _12 * temp.y + _13 * temp.z;
	out.y = _21 * temp.x + _22 * temp.y + _23 * temp.z;
	out.z = _31 * temp.x + _32 * temp.y + _33 * temp.z;
}

float MthMatrixColumnMajor::Determinant() const
{
	MthVector4 v1(_11, _12, _13, _14);
	MthVector4 v2(_21, _22, _23, _24);
	MthVector4 v3(_31, _32, _33, _34);

	MthVector4 minor;
	minor.Cross(v1, v2, v3);
	return -(_41 * minor.x + _42 * minor.y + _43 * minor.z + _44 * minor.w);
}

bool MthMatrixColumnMajor::Inverse(MthMatrixColumnMajor& out, const MthMatrixColumnMajor& in)
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

				vec[a].x = in.d[0][j];
				vec[a].y = in.d[1][j];
				vec[a].z = in.d[2][j];
				vec[a].w = in.d[3][j];
			}
		}

		v.Cross(vec[0], vec[1], vec[2]);

		for (int j = 0; j < 4; j++)
			out.d[i][j] = pow(-1.0f, i) * v[j] / det;
	}
	return true;
}