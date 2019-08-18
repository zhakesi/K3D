#pragma once
#include "KCore/KDef.h"
#include "KVectX.h"

namespace KMath 
{
	class KLIB_EXPORT KMatrix3
	{
	public:
		KMatrix3();
		KMatrix3(float a00, float a01, float a02,
			float a10, float a11, float a12,
			float a20, float a21, float a22);
		~KMatrix3();
		KMatrix3 operator *(const KMatrix3 &mat);
		KVect3 operator *(const KVect3 &v);
		KMatrix3 Transpose();
	public:
		static KMatrix3 UnitMatrix();
		static KMatrix3 RotateX(float angle);
		static KMatrix3 RotateY(float angle);
		static KMatrix3 RotateZ(float angle);
	public:
		float m[3][3];
	};

	/////////////////////////////////////////////////////////////////////////
	class KLIB_EXPORT KMatrix4
	{
	public:
		KMatrix4();
		KMatrix4(float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33);
		~KMatrix4();
		KMatrix4 operator *(const KMatrix4 &mat);
		KMatrix4 Transpose();
		float *ptr();
	public:
		static KMatrix4 UnitMatrix();
		static KMatrix4 Translation(float x, float y, float z);
		static KMatrix4 Scale(float sx, float sy, float sz);
		static KMatrix4 RotateX(float angle);
		static KMatrix4 RotateY(float angle);
		static KMatrix4 RotateZ(float angle);
		static KMatrix4 Perspective(float fov, float aspect, float znear, float zfar);
	public:
		float m[4][4];
	};
}