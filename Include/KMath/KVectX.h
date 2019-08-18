#pragma once
#include "KCore/KDef.h"
namespace KMath {
	class KLIB_EXPORT KVect2 
	{
	public:
		KVect2(float vx = 0.0, float vy = 0.0);
		KVect2(const KVect2& v);
		~KVect2() {};
		KVect2 operator +(const KVect2 &vec);
		KVect2 operator *(float v);
		KVect2 operator -(const KVect2 &vec);
	public:
		float x;
		float y;
	};

	class KLIB_EXPORT KVect3
	{
	public:
		KVect3(float vx = 0.0, float vy = 0.0, float vz = 0.0);
		KVect3(const KVect3& v);
		~KVect3() {};
		KVect3 operator +(const KVect3 &vec);
		KVect3 operator *(float v);
		KVect3 operator -(const KVect3 &vec);
		KVect3 Normalize();
		KVect3 Cross(const KVect3 &v);
	public:
		float x;
		float y;
		float z;
	};
}