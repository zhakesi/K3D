#pragma once
#include "KCore/KDef.h"
#include "KCore/KImage.h"
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "GLES3/gl3.h"

namespace KGraphic
{
	class KLIB_EXPORT KTexture
	{
	public:
		KTexture(const char *path);
		~KTexture();
	private:
		GLenum TEXTURE_PIXEL_FORMAT(int pixel_format);
	public:
		GLuint txtID;
	};
}