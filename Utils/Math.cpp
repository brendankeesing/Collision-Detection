#include "Math.h"

void MthMatrixHeighted(MthMatrix& mat, MthVector3& campos, MthVector2& camzoom, MthVector2& camvisible, float height)
{
	mat._11 = 2.0f / camzoom.x;
	mat._12 = 0.0f;
	mat._13 = 0.0f;
	mat._14 = -2.0f * campos.x / camzoom.x;

	mat._21 = 0.0f;
	mat._22 = 2.0f / camzoom.y;
	mat._23 = 2.0f * height / camzoom.y;
	mat._24 = -2.0f * (campos.y + height * campos.z) / camzoom.y;

	mat._31 = 0.0f;
	mat._32 = 0.0f;
	mat._33 = -1.0f / (camvisible.y - camvisible.x);
	mat._34 = camvisible.y / (camvisible.y - camvisible.x);

	mat._41 = 0.0f;
	mat._42 = 0.0f;
	mat._43 = 0.0f;
	mat._44 = 1.0f;
}