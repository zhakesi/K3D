#include "KGraphic/KMesh.h"

namespace KGraphic
{
	KMesh::KMesh(VertexBuffer vb, IndexBuffer ib)
	{
		m_vb = vb;
		m_ib = ib;

		this->VAO = 0;
		this->VBO = 0;
		this->EBO = 0;
		
		setupMesh();
	}
	KMesh::~KMesh()
	{
		if (this->VAO) {
			glDeleteVertexArrays(1, &this->VAO);
			this->VAO = 0;
		}
		if (this->VBO) {
			glDeleteBuffers(1, &this->VBO);
			this->VBO = 0;
		}
		if (this->EBO) {
			glDeleteBuffers(1, &this->EBO);
			this->EBO = 0;
		}
	}

	void KMesh::BlindMaterial(KMaterial *material)
	{
		this->material = material;
	}

	void KMesh::Render()
	{
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, m_ib.nr, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void KMesh::setupMesh() 
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vb.nr * sizeof(KVertex),
			&m_vb.vertexs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ib.nr * sizeof(GLuint),
			&m_ib.indices[0], GL_STATIC_DRAW);

		// 设置顶点坐标指针
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(KVertex),
			(GLvoid*)0);
		// 设置法线指针
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(KVertex),
			(GLvoid*)(sizeof(KMath::KVect3)));
		// 设置顶点的纹理坐标
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(KVertex),
			(GLvoid*)(2 * sizeof(KMath::KVect3)));

		glBindVertexArray(0);
	}
}
