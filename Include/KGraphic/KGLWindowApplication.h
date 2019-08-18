#pragma once
#include "KCore/KWindowApplication.h"
#include "KGraphic/KScene.h"
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "GLES3/gl3.h"

namespace KGraphic {
	class KLIB_EXPORT KGLWindowApplication : public KCore::KWindowApplication
	{
	public:
		KGLWindowApplication(int width, int height, const std::wstring title);
		~KGLWindowApplication();
		virtual int Initialize();
		virtual void Finalize();
	protected:
		int EGLInit(HWND hwnd, EGLDisplay &display, EGLSurface &surface);
		virtual int Render();
		virtual void FrameWorkFun();

		EGLDisplay m_display;
		EGLSurface m_surface;
	};
}