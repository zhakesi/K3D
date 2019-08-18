#pragma once
#include "KMath/KMath.h"
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "GLES3/gl3.h"
#include "KShader.h"
#include "KMaterial.h"
#include "KGraphic/KCamera.h"

namespace KGraphic
{
	struct KVertex 
	{
		KMath::KVect3 Position;
		KMath::KVect3 Normal;
		KMath::KVect2 TexCoords;
	};
	struct VertexBuffer
	{
		unsigned nr;
		KVertex *vertexs;
	};

	struct IndexBuffer
	{
		unsigned nr;
		GLuint *indices;
	};

	class KLIB_EXPORT KMesh
	{
	public:
		KMesh(VertexBuffer vb, IndexBuffer ib);
		~KMesh();
		void BlindMaterial(KMaterial *material);
		void Render();
	private:
		void setupMesh();

	public:
		KMaterial *material;
		VertexBuffer m_vb;
		IndexBuffer m_ib;
	private:
		GLuint VAO, VBO, EBO;
	};
}