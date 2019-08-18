#include "KGraphic/KScene.h"
#include "KMath/KMath.h"

using namespace KMath;

namespace KGraphic 
{
	KScene::KScene()
	{
		m_models.clear();
		m_materials.clear();
		KVect3 eye, target;
		eye = KVect3(0.0f, -0.0f, 50.0f);
		m_camera.SetPosition(eye);
		target = KVect3(0.0f, 0.0f, 0.0f);
		m_camera.SetLookAt(target);
		m_angle_yaw = 0.0f;
		m_angle_pitch = 0.0f;
		m_matrix = KMatrix4::UnitMatrix();
		m_mat_update = true;
	}
	KScene::~KScene()
	{

	}

	void KScene::AddModel(KModel* model)
	{
		m_models.push_back(model);
	}

	void KScene::AddMaterial(KMaterial *material)
	{
		m_materials.push_back(material);
	}

	void KScene::Render()
	{
		glEnable(GL_DEPTH_TEST);
		std::vector<KModel *>::iterator it;
		KMatrix4 scene_mat = GetMatrix();
		for (it = m_models.begin(); it < m_models.end(); it++) {
			KModel *model = *it;
			model->Render(&m_camera, scene_mat);
		}
	}

	KCamera* KScene::GetCamera()
	{
		return &m_camera;
	}
	KMath::KMatrix4 KScene::GetMatrix()
	{
		if (!m_mat_update)
			return m_matrix;
		m_mat_update = false;
		KMatrix4 mat_yaw = KMatrix4::RotateY(m_angle_yaw);
		KMatrix4 mat_pitch = KMatrix4::RotateX(m_angle_pitch);
		m_matrix = mat_pitch * mat_yaw;
		return m_matrix;
	}
	void KScene::RotationY(float angle)
	{
		m_angle_yaw += angle;
		m_angle_yaw = KMK::ClampCircleVal(m_angle_yaw, 0.0f, 360.0f);
		m_mat_update = true;
	}

	void KScene::RotationX(float angle) 
	{
		m_angle_pitch += angle;
		m_angle_pitch = KMK::ClampCircleVal(m_angle_pitch, 0.0f, 360.0f);
		m_mat_update = true;
	}
}