#pragma once

#include "KCore/KDef.h"
#include "KGraphic/KModel.h"
#include "KGraphic/KCamera.h"
#include "KGraphic/KMaterial.h"
#include <vector>

namespace KGraphic
{
	class KLIB_EXPORT KScene
	{
	public:
		KScene();
		~KScene();
		void AddModel(KModel* model);
		void AddMaterial(KMaterial *material);
		void Render();
		KCamera *GetCamera();
		KMath::KMatrix4 GetMatrix();
		void RotationY(float angle);
		void RotationX(float angle);
	private:
#pragma warning(push)
#pragma warning(disable:4251)
		std::vector<KModel*> m_models;
		std::vector<KMaterial*> m_materials;
#pragma warning(pop)
		KCamera m_camera;
		bool m_mat_update;
		float m_angle_yaw;
		float m_angle_pitch;
		KMath::KMatrix4 m_matrix;
	};
}