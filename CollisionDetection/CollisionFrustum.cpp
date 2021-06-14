#include "CollisionFrustum.h"

static void trasformperspective(MthVector3& out, const MthVector3& point, const MthMatrix& mat)
{
	MthVector4 temppoint(point.x, point.y, point.z, 1.0f);
	MthVector4 tempout;

	mat.Transform(tempout, temppoint);
	out = (MthVector3&)tempout * (1.0f / tempout.w);
}

void CollisionFrustum::GetCenterPoint(MthVector3& out) const
{
	// calculates the average of all vertices
	out = MthVector3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 8; ++i)
		out += _vertices[i];
	out *= 1.0f / 6.0f;
}

float CollisionFrustum::GetFurthestDistance(const MthVector3& point) const
{
	float furthestdist = _vertices[0].LengthSqr();
	float temp;
	for (int i = 1; i < 6; ++i)
	{
		temp = _vertices[i].LengthSqr();
		if (temp > furthestdist)
			furthestdist = temp;
	}
	return sqrtf(furthestdist);
}

bool CollisionFrustum::IntersectAABB(const MthVector3& p, const MthVector3& dimensions) const
{
	for (int i = 0; i < 6; ++i)
	{
		MthVector3 cp(_planes[i].a > 0.0f ? p.x - dimensions.x : p.x + dimensions.x,
					  _planes[i].b > 0.0f ? p.y - dimensions.y : p.y + dimensions.y,
					  _planes[i].c > 0.0f ? p.z - dimensions.z : p.z + dimensions.z);
		float distance =_planes[i].a * cp.x + _planes[i].b * cp.y + _planes[i].c * cp.z + _planes[i].d;
		if (distance >= 0.0f)
			return false;
	}

	return true;
}

bool CollisionFrustum::IntersectPoint(const MthVector3& p) const
{
	for (int i = 0; i < 6; ++i)
	{
		float distance =_planes[i].a * p.x + _planes[i].b * p.y + _planes[i].c * p.z + _planes[i].d;
		if (distance >= 0.0f)
			return false;
	}

	return true;
}

bool CollisionFrustum::IntersectSphere(const MthVector3& p, float radius) const
{
	for (int i = 0; i < 6; ++i)
	{
		float distance =_planes[i].a * p.x + _planes[i].b * p.y + _planes[i].c * p.z + _planes[i].d;
		if (distance >= radius)
			return false;
	}

	return true;
}

void CollisionFrustum::Recalculate(const MthMatrix& viewprojection)
{
	MthMatrix invviewprojection;
	if (!invviewprojection.Inverse(viewprojection))
		return;

	// front/near verts
	trasformperspective(_vertices[0], MthVector3(-1.0f, -1.0f, 0.0f), invviewprojection);
	trasformperspective(_vertices[1], MthVector3(-1.0f,  1.0f, 0.0f), invviewprojection);
	trasformperspective(_vertices[2], MthVector3( 1.0f,  1.0f, 0.0f), invviewprojection);
	trasformperspective(_vertices[3], MthVector3( 1.0f, -1.0f, 0.0f), invviewprojection);

	// back/far verts
	trasformperspective(_vertices[4], MthVector3(-1.0f, -1.0f, 1.0f), invviewprojection);
	trasformperspective(_vertices[5], MthVector3(-1.0f,  1.0f, 1.0f), invviewprojection);
	trasformperspective(_vertices[6], MthVector3( 1.0f,  1.0f, 1.0f), invviewprojection);
	trasformperspective(_vertices[7], MthVector3( 1.0f, -1.0f, 1.0f), invviewprojection);

	_calculatefromvertices();
}

void CollisionFrustum::_calculatefromvertices()
{
	_planes[0].FromPoints(_vertices[0], _vertices[1], _vertices[2]); // front
	_planes[1].FromPoints(_vertices[4], _vertices[6], _vertices[5]); // back
	_planes[2].FromPoints(_vertices[0], _vertices[4], _vertices[1]); // left
	_planes[3].FromPoints(_vertices[2], _vertices[6], _vertices[3]); // right
	_planes[4].FromPoints(_vertices[1], _vertices[5], _vertices[2]); // top
	_planes[5].FromPoints(_vertices[0], _vertices[3], _vertices[4]); // bottom

	for (int i = 0; i < 6; ++i)
		_planes[i].Normalize();
}