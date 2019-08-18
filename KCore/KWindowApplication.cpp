#include "KCore/KWindowApplication.h"
#include <iostream>

namespace KCore 
{
	KWindowApplication::KWindowApplication(int width, int height, const std::wstring title)
	{
		m_win_width = width;
		m_win_height = height;
		m_title = title;
	}

	KWindowApplication::~KWindowApplication() 
	{

	}

	int KWindowApplication::Initialize()
	{
		KBaseApplication::Initialize();

		m_wind = CreateEmptyWindow(m_win_width, m_win_height, m_title);
		return 0;
	}

	// Finalize all sub modules and clean up all runtime temporary files.
	void KWindowApplication::Finalize()
	{

	}


	// One cycle of the main loop
	int KWindowApplication::Run()
	{
		ShowWindow(m_wind, SW_SHOWDEFAULT);
		UpdateWindow(m_wind);

		while (!m_quit) {
			MSG msg = {};
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				FrameMessageFun(msg);
				DispatchMessage(&msg);
			} else {
				FrameWorkFun();
			}
		}
		return KR_SUCCESS;
	}

	HWND KWindowApplication::CreateEmptyWindow(int width, int height, const std::wstring title)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASSEX windowClass = { 0 };
		const std::wstring strClassName(L"KGameWindow");
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = hInstance;
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.lpszClassName = strClassName.c_str();
		RegisterClassEx(&windowClass);

		RECT windowRect =
		{
			0, 0,
			static_cast<LONG>(width),
			static_cast<LONG>(height)
		};
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

		HWND hwnd = CreateWindow(
			windowClass.lpszClassName,
			title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			hInstance,
			NULL);

		return hwnd;
	}

	LRESULT CALLBACK KWindowApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
