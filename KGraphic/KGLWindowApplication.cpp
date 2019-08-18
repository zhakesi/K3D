#include "KGraphic/KGLWindowApplication.h"
#include <iostream>

using namespace KCore;

namespace KGraphic
{
	KGLWindowApplication::KGLWindowApplication(int width, int height, const std::wstring title):
		KWindowApplication(width, height, title)
	{

	}

	KGLWindowApplication::~KGLWindowApplication()
	{

	}

	int KGLWindowApplication::Initialize()
	{
		KWindowApplication::Initialize();
		EGLInit(m_wind, m_display, m_surface);

		return 0;
	}

	// Finalize all sub modules and clean up all runtime temporary files.
	void KGLWindowApplication::Finalize()
	{

		KWindowApplication::Finalize();
	}

	int KGLWindowApplication::EGLInit(HWND hwnd, EGLDisplay &display, EGLSurface &surface)
	{
		const EGLint attribs[] =
		{
			EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 16,
			EGL_SAMPLE_BUFFERS, 1,
			EGL_SAMPLES, 4,
			EGL_NONE
		};
		EGLint conAttribs[] = {
			EGL_CONTEXT_CLIENT_VERSION, 3,
			EGL_NONE };

		HDC hDC = GetDC(hwnd);
		display = eglGetDisplay(hDC);
		if (display == EGL_NO_DISPLAY)
		{
			printf("eglGetDisplay Failed.\n");
			return EGL_FALSE;
		}
		EGLint major, minor;
		if (!eglInitialize(display, &major, &minor))
		{
			printf("eglInitialize Failed.\n");
			return EGL_FALSE;
		}
		EGLConfig config;
		EGLint numConfigs;
		if (!eglChooseConfig(display, attribs, &config, 1,
			&numConfigs))
		{
			printf("eglChooseConfig Failed.\n");
			return EGL_FALSE;
		}
		surface = eglCreateWindowSurface(display, config,
			hwnd, NULL);
		if (surface == EGL_NO_SURFACE)
		{
			printf("eglCreateWindowSurface Failed.\n");
			return EGL_FALSE;
		}
		eglBindAPI(EGL_OPENGL_ES_API);
		EGLContext context = eglCreateContext(display, config,
			NULL, conAttribs);
		if (context == EGL_NO_CONTEXT)
		{
			printf("eglCreateContext Failed.\n");
			return EGL_FALSE;
		}
		if (!eglMakeCurrent(display, surface, surface, context))
		{
			printf("eglMakeCurrent Failed.\n");
			return EGL_FALSE;
		}
		printf("EGL Init Sucessfully.\n");

		return EGL_SUCCESS;
	}

	int KGLWindowApplication::Render() 
	{
		float color[] = { 0.3f, 0.2f, 0.5f };
		glClearColor(color[0], color[1], color[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		eglSwapBuffers(m_display, m_surface);
		return KR_SUCCESS;
	}
	void KGLWindowApplication::FrameWorkFun()
	{
		Render();
		Sleep(10);
	}
}
