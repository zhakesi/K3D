#pragma once

#include "KCore/KDef.h"
#include "KMath/KMath.h"
#include "KGraphic/KShader.h"
#include "KGraphic/KTexture.h"

namespace KGraphic 
{
	enum
	{
		GRAPHIC_MATERIAL_NULL = 0,
		GRAPHIC_MATERIAL_1,
		GRAPHIC_MATERIAL_2,
		GRAPHIC_MATERIAL_NR = 256,
	};

	enum
	{
		GRAPH_MATERIAL_BLINN_PROP_SHADER = 0,
		GRAPH_MATERIAL_BLINN_PROP_PACK,
		GRAPH_MATERIAL_BLINN_PROP_AMBIENT,
		GRAPH_MATERIAL_BLINN_PROP_DIFFUSE,
		GRAPH_MATERIAL_BLINN_PROP_SPECULAR,
		GRAPH_MATERIAL_BLINN_PROP_SHININESS,
		GRAPH_MATERIAL_BLINN_PROP_TEXTURE,

	};

	class KLIB_EXPORT KMaterial
	{
	public:
		virtual void SetProperty(int prop_id, void *property) = 0;
		virtual void GetProperty(int prop_id, void *property) = 0;
		virtual void Active() = 0;
		void BindShader(KShader *shader);
		KShader *GetBindingShader();
	public:
		int ID;
		KShader *shader;
	};
	
	struct BlinnMaterialPack
	{
		float ambient_k;
		float diffuse_k;
		float specular_k;
		float shininess;
		GLuint texID;
	};

	class KLIB_EXPORT KBlinnMaterial : public KMaterial
	{
	public:
		KBlinnMaterial();
		~KBlinnMaterial();

		virtual void SetProperty(int prop_id, void *property);
		virtual void GetProperty(int prop_id, void *property);
		virtual void Active();
	private:
		BlinnMaterialPack property_list;
	};
}