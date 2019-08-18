#include "KMath/KVectX.h"
#include <math.h>

namespace KMath 
{
	KVect2::KVect2(float vx, float vy) :
		x(vx), y(vy)
	{

	}

	KVect2::KVect2(const KVect2& vc) :
		x(vc.x), y(vc.y)
	{

	}

	KVect2 KVect2::operator +(const KVect2 &vec)
	{
		return KVect2(x + vec.x, y + vec.y);
	}

	KVect2 KVect2::operator *(float v)
	{
		return KVect2(x * v, y * v);
	}

	KVect2 KVect2::operator -(const KVect2 &vec)
	{
		return KVect2(x - vec.x, y - vec.y);
	}

	/////////////////////////////////////////////////////////////////////////////
	KVect3::KVect3(float vx, float vy, float vz) :
		x(vx), y(vy), z(vz)
	{

	}

	KVect3::KVect3(const KVect3& vc) :
		x(vc.x), y(vc.y), z(vc.z)
	{

	}

	KVect3 KVect3::operator +(const KVect3 &vec)
	{
		return KVect3(x + vec.x, y + vec.y, z + vec.z);
	}

	KVect3 KVect3::operator *(float v)
	{
		return KVect3(x * v, y * v, z * v);
	}

	KVect3 KVect3::operator -(const KVect3 &vec)
	{
		return KVect3(x - vec.x, y - vec.y, z - vec.z);
	}

	KVect3 KVect3::Normalize()
	{
		float length = sqrtf(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;

		return KVect3(x, y, z);
	}

	KVect3 KVect3::Cross(const KVect3 &v)
	{
		return KVect3(y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}
}
