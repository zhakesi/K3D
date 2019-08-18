#pragma once
#include "KCore/Kdef.h"
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "GLES3/gl3.h"

namespace KGraphic
{
	class KLIB_EXPORT KShader
	{
	public:
		KShader();
		KShader(const char* vpath, const char* fpath);
		~KShader();
		void Use();
	private:
		GLuint CompileShaderFile(const char* path, GLenum type);
	public:
		GLuint m_program;
	};
}