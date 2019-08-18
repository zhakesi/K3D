#pragma once
#include "KCore/KDef.h"
#include "KMath/KVectX.h"
#include "KMath/KMatrix.h"

namespace KGraphic 
{
	class KLIB_EXPORT KCamera
	{
	public:
		KCamera();
		KCamera(KMath::KVect3 &eye, KMath::KVect3 &upDir);
		~KCamera();
		KMath::KMatrix4 GetViewMatrix();
		KMath::KMatrix4 GetPerspMatrix();
		void SetPosition(KMath::KVect3 &eye);
		KMath::KVect3 GetPosition();
		void SetLookAt(KMath::KVect3 &targetP);
		void WalkForward(float dist);
		void WalkBackward(float dist);
		void WalkLeftward(float dist);
		void WalkRightward(float dist);
		void RotationX(float angle);
		void RotationY(float angle);
		void RotationZ(float angle);
	private:
		void Update();
		void UpdateMatrix();
	private:
		int m_need_update;
		KMath::KVect3 m_eye;
		KMath::KVect3 m_target;
		KMath::KVect3 m_upWorld;
		KMath::KMatrix4 m_viewMat;
	};
}