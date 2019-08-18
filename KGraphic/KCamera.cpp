#include "KGraphic/KCamera.h"
#include "KMath/KMath.h"
#include <math.h>
using namespace KMath;

namespace KGraphic
{
	KCamera::KCamera()
	{
		m_eye = KVect3(0.0, 0.0, 1.0);
		m_target = KVect3(0.0, 0.0, -1.0);
		m_upWorld = KVect3(0.0, 1.0, 0.0);

		m_need_update = true;
		Update();
	}

	KCamera::KCamera(KVect3 &eye, KVect3 &upDir)
	{
		m_eye = eye;
		m_target = KVect3(0.0, 0.0, -1.0);
		m_upWorld = KVect3(0.0, 1.0, 0.0);

		m_need_update = true;
		Update();
	}

	void KCamera::Update()
	{
		if (!m_need_update)
			return;

		UpdateMatrix();

		m_need_update = false;
	}

	KMatrix4 KCamera::GetViewMatrix()
	{
		Update();
		return m_viewMat;
	}

	KMatrix4 KCamera::GetPerspMatrix()
	{
		static const KMatrix4 mat = 
			KMatrix4::Perspective(45.0f, 1024.0f / 720.0f, 1.0f, 500.0f);
		return mat;
	}

	KCamera::~KCamera()
	{

	}

	void KCamera::UpdateMatrix()
	{
		KMatrix4 trans_mat(1.0, 0.0, 0.0, -m_eye.x,
			0.0, 1.0, 0.0, -m_eye.y,
			0.0, 0.0, 1.0, -m_eye.z,
			0.0, 0.0, 0.0, 1.0);
		
		KVect3 N, V, U;
		N = m_target.Normalize();
		V = m_upWorld.Normalize();
		U = V.Cross(N);

		KMatrix4 rote_mat = KMatrix4(U.x, U.y, U.z, 0.0,
			V.x, V.y, V.z, 0.0,
			N.x, N.y, N.z, 0.0,
			0.0, 0.0, 0.0, 1.0);

		m_viewMat = rote_mat * trans_mat;
	}
	void KCamera::SetPosition(KMath::KVect3 &eye)
	{
		m_eye = eye;
		m_need_update = true;
	}

	KVect3 KCamera::GetPosition()
	{
		return m_eye;
	}

	void KCamera::SetLookAt(KMath::KVect3 &targetP)
	{
		m_target = targetP - m_eye;
		m_need_update = true;
	}

	void KCamera::RotationX(float angle)
	{
		KMatrix3 rot_mat = KMatrix3::RotateX(angle);
		m_upWorld = rot_mat * m_upWorld;
		m_upWorld = m_upWorld.Normalize();
		m_need_update = true;
	}

	void KCamera::RotationY(float angle)
	{
		KMatrix3 rot_mat = KMatrix3::RotateY(angle);
		m_target = rot_mat * m_target;
		m_target = m_target.Normalize();
		m_need_update = true;
	}

	void KCamera::RotationZ(float angle)
	{
		KMatrix3 rot_mat = KMatrix3::RotateZ(angle);
		m_upWorld = rot_mat * m_upWorld;
		m_upWorld = m_upWorld.Normalize();
		m_need_update = true;
	}

	void KCamera::WalkForward(float dist)
	{
		m_eye = m_eye + (m_target * dist);
		m_need_update = true;
	}

	void KCamera::WalkBackward(float dist)
	{
		m_eye = m_eye - (m_target * dist);
		m_need_update = true;
	}

	void KCamera::WalkLeftward(float dist)
	{
		KVect3 dir = m_target.Cross(m_upWorld);
		m_eye = m_eye - (dir * dist);
		m_need_update = true;
	}

	void KCamera::WalkRightward(float dist)
	{
		KVect3 dir = m_target.Cross(m_upWorld);
		m_eye = m_eye + (dir * dist);
		m_need_update = true;
	}
}