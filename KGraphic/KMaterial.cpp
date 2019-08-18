#include "KGraphic/KMaterial.h"
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "GLES3/gl3.h"
#include "KGraphic/KCamera.h"

#include "KMath/KMath.h"
using namespace KMath;
#include <time.h>

namespace KGraphic
{
	void KMaterial::BindShader(KShader *shader)
	{
		this->shader = shader;
	}

	KShader* KMaterial::GetBindingShader()
	{
		return shader;
	}

	KBlinnMaterial::KBlinnMaterial()
	{
		this->ID = GRAPHIC_MATERIAL_NULL;
	}
	
	KBlinnMaterial::~KBlinnMaterial() 
	{

	}

	void KBlinnMaterial::SetProperty(int prop_id, void *property) 
	{
		switch (prop_id)
		{
		case GRAPH_MATERIAL_BLINN_PROP_SHADER:
			shader = (KShader *)(property);
			break;
		case GRAPH_MATERIAL_BLINN_PROP_PACK:
			property_list = *(BlinnMaterialPack *)(property);
			break;
		//case GRAPH_MATERIAL_BLINN_PROP_AMBIENT:
		//	property_list.ambient = *(KVect3 *)(property);
		//	break;
		//case GRAPH_MATERIAL_BLINN_PROP_DIFFUSE:
		//	property_list.diffuse = *(KVect3 *)(property);
		//	break;
		//case GRAPH_MATERIAL_BLINN_PROP_SPECULAR:
		//	property_list.diffuse = *(KVect3 *)(property);
		//	break;
		//case GRAPH_MATERIAL_BLINN_PROP_SHININESS:
		//	property_list.shininess = *(float *)(property);
		//	break;
		//case GRAPH_MATERIAL_BLINN_PROP_TEXTURE:
		//	property_list.texID = *(GLuint *)(property);
		//	break;
		default:
			break;
		}
	}

	void KBlinnMaterial::GetProperty(int prop_id, void *property) 
	{

	}
	static KMatrix4 RotY() 
	{
		static float rote = 0.0f;
		float rote_k = 360.0f / (6 * CLOCKS_PER_SEC);
		static clock_t pre = clock();
		clock_t cur = clock();
		if (cur - pre > 0) {
			rote += rote_k * (cur - pre);
			pre = cur;
		}
		if (rote > 360.0f)
			rote -= 360.0f;
		return KMatrix4::RotateY(rote);
	}
	void KBlinnMaterial::Active()
	{
		GLuint program = shader->m_program;
		glUniform1i(glGetUniformLocation(program, "text"), 0);

		glUniform1f(glGetUniformLocation(program, "ambient_k"), property_list.ambient_k);
		glUniform1f(glGetUniformLocation(program, "diffuse_k"), property_list.diffuse_k);
		glUniform1f(glGetUniformLocation(program, "specular_k"), property_list.specular_k);
		glUniform1f(glGetUniformLocation(program, "shininess"), property_list.shininess);

		glBindTexture(GL_TEXTURE_2D, property_list.texID);
		glActiveTexture(GL_TEXTURE0);
	}
}
