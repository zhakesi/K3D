#pragma once

#include "KCore/KDef.h"
#include "KGraphic/KMesh.h"
#include "KGraphic/KMaterial.h"
#include "KGraphic/KCamera.h"
#include "KMath/KVectX.h"
#include <vector>

namespace KGraphic
{
	class KLIB_EXPORT KModel
	{
	public:
		KModel();
		~KModel();
		int LoadFile(const char *path);
		void BlindMaterial(KMaterial *material);
		void Render(KCamera *camera, KMath::KMatrix4 &scene_rote);
		void BindTexture(KTexture *tex);
	public:
		KMath::KMatrix4 GetMatrix();
		KMath::KMatrix4 GetRoteMatrix();
		void SetSizeScale(float scale);
		void SetPosition(KMath::KVect3 &position);
		void RoteYaw(float angle);
		void RotePitch(float angle);
		void RoteRoll(float angle);
#pragma warning(push)
#pragma warning(disable:4251)
		std::vector <KMesh *> m_meshes;
#pragma warning(pop)
		bool m_mat_update;
		KMaterial *m_material;
		float m_scale;
		KMath::KVect3 m_position;
		float m_rote_yaw;
		float m_rote_pitch;
		float m_rote_roll;
		KMath::KMatrix4 m_matrix;
		KMath::KMatrix4 m_rot_matrix;
	};
}