#include "CommonIncludes.h"

namespace GUI
{
	HWND WindowHWND;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//  Terminate the entire process if we close the GUI
		if (uMsg == WM_CLOSE)
			exit(0);

		return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}

	void Init(HINSTANCE hInstance, int nShowCmd)
	{
		WNDCLASS window_class = {};
		window_class.lpfnWndProc = WndProc;
		window_class.style = 0;
		window_class.hInstance = hInstance;
		window_class.lpszClassName = "HardwareQueryWindow";

		// Register our window class
		if (!RegisterClassA(&window_class))
			throw std::exception("Failed to register window class " __FUNCTION__);

		// Create our window
		WindowHWND = CreateWindowExA(0, "HardwareQueryWindow", "HardwareQuery", WS_SYSMENU, 0, 0, 640, 480, nullptr, nullptr, hInstance, nullptr);

		if (!WindowHWND)
			throw std::exception("Failed to create window " __FUNCTION__);

		// Show and update our window
		ShowWindow(WindowHWND, nShowCmd);
		
		if (!UpdateWindow(WindowHWND))
			throw std::exception("UpdateWindow failed " __FUNCTION__);

		MSG Msg = {};

		// Dispatch messages, update as needed, etc
		while (GetMessageA(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}
	}
}