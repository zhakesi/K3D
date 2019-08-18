#include "KMath/KMatrix.h"
#include "KMath/KMK.h"
#include <math.h>

namespace KMath 
{
	KMatrix3::KMatrix3()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;

		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;

		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
	}

	KMatrix3::KMatrix3(float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22)
	{
		m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;

		m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;

		m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
	}

	KMatrix3::~KMatrix3()
	{

	}

	KMatrix3 KMatrix3::operator *(const KMatrix3 &mat)
	{
		KMatrix3 ret;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ret.m[i][j] = m[i][0] * mat.m[0][j] +
					m[i][1] * mat.m[1][j] +
					m[i][2] * mat.m[2][j];
			}
		}
		return ret;
	}

	KVect3 KMatrix3::operator *(const KVect3 &v)
	{
		KVect3 ret;
		ret.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
		ret.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
		ret.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
		return ret;
	}

	KMatrix3 KMatrix3::UnitMatrix()
	{
		KMatrix3 matrix(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f);
		return matrix;
	}

	KMatrix3 KMatrix3::RotateX(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix3 matrix(1.0f, 0.0f, 0.0f,
			0.0f, cosf(rad), -sinf(rad),
			0.0f, sinf(rad), cosf(rad));
		return matrix;
	}

	KMatrix3 KMatrix3::RotateY(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix3 matrix(cosf(rad), 0.0f, -sinf(rad),
			0.0f, 1.0f, 0.0f,
			sinf(rad), 0.0f, cosf(rad));
		return matrix;
	}

	KMatrix3 KMatrix3::RotateZ(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix3 matrix(cosf(rad), -sinf(rad), 0.0f,
			sinf(rad), cosf(rad), 0.0f,
			0.0f, 0.0f, 1.0f);
		return matrix;
	}

	KMatrix3 KMatrix3::Transpose()
	{
		KMatrix3 matrix(m[0][0], m[1][0], m[2][0],
			m[0][1], m[1][1], m[2][1],
			m[0][2], m[1][2], m[2][2]);
		return matrix;
	}

	//////////////////////////////////////////////////////////////////
	KMatrix4::KMatrix4()
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;

		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;

		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;

		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}

	KMatrix4::KMatrix4(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33)
	{
		m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;

		m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;

		m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;

		m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
	}

	KMatrix4::~KMatrix4()
	{

	}

	KMatrix4 KMatrix4::operator *(const KMatrix4 &mat)
	{
		KMatrix4 ret;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][0] * mat.m[0][j] +
					m[i][1] * mat.m[1][j] +
					m[i][2] * mat.m[2][j] +
					m[i][3] * mat.m[3][j];
			}
		}
		return ret;
	}

	KMatrix4 KMatrix4::UnitMatrix()
	{
		KMatrix4 matrix(1.0f, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		return matrix;
	}

	KMatrix4 KMatrix4::Translation(float tx, float ty, float tz)
	{
		KMatrix4 matrix(1.0f, 0.0f, 0.0f, tx,
			0.0f, 1.0f, 0.0f, ty,
			0.0f, 0.0f, 1.0f, tz,
			0.0f, 0.0f, 0.0f, 1.0f);

		return matrix;
	}
	KMatrix4 KMatrix4::Scale(float sx, float sy, float sz)
	{
		KMatrix4 matrix(sx, 0.0f, 0.0f, 0.0f,
			0.0f, sy, 0.0f, 0.0f,
			0.0f, 0.0f, sz, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return matrix;
	}
	KMatrix4 KMatrix4::RotateX(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix4 matrix(1.0f, 0.0f, 0.0f, 0.0f,
			0.0, cosf(rad), -sinf(rad), 0.0f,
			0.0f, sinf(rad), cosf(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		return matrix;
	}

	KMatrix4 KMatrix4::RotateY(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix4 matrix(cosf(rad), 0.0f, -sinf(rad), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(rad), 0.0f, cosf(rad), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		return matrix;
	}

	KMatrix4 KMatrix4::RotateZ(float angle)
	{
		float rad = KMK::Angle2Radian(angle);
		KMatrix4 matrix(cosf(rad), -sinf(rad), 0.0f, 0.0f,
			sinf(rad), cosf(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		return matrix;
	}

	KMatrix4 KMatrix4::Perspective(float fov, float aspect, float znear, float zfar)
	{
		float tanHalfFov = tanf(KMK::Angle2Radian(fov / 2.0f));
		float a00 = 1.0f / (tanHalfFov * aspect);
		float a11 = 1.0f / tanHalfFov;
		float a22 = (-znear - zfar) / (znear - zfar);
		float a23 = 2.0f * zfar * znear / (znear - zfar);

		KMatrix4 matrix(a00, 0.0f, 0.0f, 0.0f,
			0.0f, a11, 0.0f, 0.0f,
			0.0f, 0.0f, a22, a23,
			0.0f, 0.0f, 1.0f, 0.0f);
		return matrix;
	}

	KMatrix4 KMatrix4::Transpose()
	{
		KMatrix4 matrix(m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3]);
		return matrix;
	}

	float *KMatrix4::ptr()
	{
		return &m[0][0];
	}
}