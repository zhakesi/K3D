#include "KGraphic/KModel.h"
#include <iostream>
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"
#include "KMath/KMath.h"
using namespace KMath;

namespace KGraphic 
{
	KModel::KModel() 
	{
		m_scale = 1.0f;
		m_position = KVect3(0.0f, 0.0f, 0.0f);
		m_rote_yaw = 0.0f;
		m_rote_pitch = 0.0f;
		m_rote_roll = 0.0f;
		m_matrix = KMatrix4::UnitMatrix();
		m_rot_matrix = KMatrix4::UnitMatrix();
		m_mat_update = true;
	}
	
	KModel::~KModel() 
	{

	}

	KMesh* ConvertMesh(aiMesh* mesh)
	{
		// Data to fill
		VertexBuffer vert_buf;
		IndexBuffer idx_buf;

		vert_buf.nr = mesh->mNumVertices;
		vert_buf.vertexs = new KVertex[vert_buf.nr];
		for (unsigned i = 0; i < mesh->mNumVertices; i++)
		{
			KVertex vertex;
			// Positions
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.z = mesh->mVertices[i].y;
			vertex.Position.y = -mesh->mVertices[i].z;
			// Normals
			if (mesh->mNormals) {
				vertex.Normal.x = mesh->mNormals[i].x;
				vertex.Normal.z = mesh->mNormals[i].y;
				vertex.Normal.y = -mesh->mNormals[i].z;
			} else {
				vertex.Normal.x = 0.0;
				vertex.Normal.y = 0.0;
				vertex.Normal.z = 0.0;
			}
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) {
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			} else {
				vertex.TexCoords.x = 0.0f;
				vertex.TexCoords.y = 0.0f;
			}
			vert_buf.vertexs[i] = vertex;
			//printf("vertexs:%.3f,%.3f,%.3f\n", 
			//vertex.Position.x, 
			//vertex.Position.y,
			//vertex.Position.z);
		}

		idx_buf.nr = 0;
		for (unsigned i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			idx_buf.nr += face.mNumIndices;
		}
		idx_buf.indices = new unsigned[idx_buf.nr];
		int count = 0;
		for (unsigned i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned j = 0; j < face.mNumIndices; j++) {
				idx_buf.indices[count++] = face.mIndices[j];
				//printf("idx value:%d\n", face.mIndices[j]);
			}
		}
		return new KMesh(vert_buf, idx_buf);
	}

	void processNode(aiNode* node, const aiScene* scene, KModel* model)
	{
		// Process each mesh located at the current node
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			KMesh *kmesh = ConvertMesh(mesh);
			model->m_meshes.push_back(kmesh);
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, model);
		}
	}

	int KModel::LoadFile(const char *path) 
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return KR_FAILED;
		}

		// Process ASSIMP's root node recursively
		processNode(scene->mRootNode, scene, this);
		return KR_SUCCESS;
	}

	void KModel::BlindMaterial(KMaterial *material)
	{
		m_material = material;
	}

	void  KModel::SetSizeScale(float scale)
	{
		m_scale = scale;
		m_mat_update = true;
	}

	void KModel::SetPosition(KMath::KVect3 &position)
	{
		m_position = position;
		m_mat_update = true;
	}

	void KModel::RoteYaw(float angle)
	{
		m_rote_yaw += angle;
		m_rote_yaw = KMK::ClampCircleVal(m_rote_yaw, 0.0f, 360.0f);
		m_mat_update = true;
	}

	void KModel::RotePitch(float angle)
	{
		m_rote_pitch += angle;
		m_rote_pitch = KMK::ClampCircleVal(m_rote_pitch, 0.0f, 360.0f);
		m_mat_update = true;
	}

	void KModel::RoteRoll(float angle) 
	{
		m_rote_roll += angle;
		m_rote_roll = KMK::ClampCircleVal(m_rote_roll, 0.0f, 360.0f);
		m_mat_update = true;
	}

	KMatrix4 KModel::GetMatrix()
	{
		if (!m_mat_update)
			return m_matrix;

		m_mat_update = false;
		
		KMatrix4 mat_scale = KMatrix4::Scale(m_scale, m_scale, m_scale);
		KMatrix4 mat_trans = KMatrix4::Translation(m_position.x,
								m_position.y, m_position.z);

		m_rot_matrix = KMatrix4::UnitMatrix();
		m_matrix = mat_trans * mat_scale * m_rot_matrix;
		return m_matrix;
	}
	KMatrix4 KModel::GetRoteMatrix()
	{
		return m_rot_matrix;
	}

	void KModel::Render(KCamera *camera, KMatrix4 &scene_rote)
	{
		KShader *shader = m_material->GetBindingShader();
		shader->Use();
		GLuint prog = shader->m_program;
		KMatrix4 mat_origin = GetMatrix();

		KMatrix4 mat_model = scene_rote * mat_origin;
		KMatrix4 mat_view = camera->GetViewMatrix();
		KMatrix4 mat_perp = camera->GetPerspMatrix();

		KMatrix4 mat_mvp = mat_perp * mat_view * mat_model;
		KMatrix4 mat_normal = scene_rote * m_rot_matrix;

		GLint location = glGetUniformLocation(prog, "mvp_mat");
		glUniformMatrix4fv(location, 1, GL_TRUE, mat_mvp.ptr());
		location = glGetUniformLocation(prog, "model_mat");
		glUniformMatrix4fv(location, 1, GL_TRUE, mat_model.ptr());
		location = glGetUniformLocation(prog, "normal_mat");
		glUniformMatrix4fv(location, 1, GL_TRUE, mat_normal.ptr());

		KVect3 eye = camera->GetPosition();
		location = glGetUniformLocation(prog, "eye");
		glUniform3fv(location, 1, &eye.x);
		m_material->Active();

		std::vector<KMesh *>::iterator it;
		KMesh *mesh;
		for (it = m_meshes.begin(); it < m_meshes.end(); it++) {
			mesh = *it;
			mesh->Render();
		}
	}
}