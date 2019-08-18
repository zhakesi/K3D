#pragma once
#include <string>
#include "KBaseApplication.h"
#include <Windows.h>

namespace KCore {
	class KLIB_EXPORT KWindowApplication : public KBaseApplication
	{
	public:
		KWindowApplication(int width, int height, const std::wstring title);
		~KWindowApplication();
		virtual int Initialize();
		virtual void Finalize();
		virtual int Run();

	protected:
		int m_win_width;
		int m_win_height;
#pragma warning(push)
#pragma warning(disable:4251)
		std::wstring m_title;
#pragma warning(pop)
		HWND m_wind;
	protected:
		virtual void FrameWorkFun() {};
		virtual void FrameMessageFun(MSG &msg) {};
	protected:
		HWND CreateEmptyWindow(int width, int height, const std::wstring title);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}