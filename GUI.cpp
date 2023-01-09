#include "CommonIncludes.h"

namespace GUI
{
	HWND WindowHWND;
	
	namespace Controls
	{
		HWND MemoryUsageLabel;

		// Wrapper functions
		HWND CreateLabel(const std::string& Text, int X, int Y, HINSTANCE hInstance)
		{
			return CreateWindowExA(0l, "STATIC", Text.c_str(), WS_VISIBLE | WS_CHILD | SS_LEFT, X, Y, 400, 100, WindowHWND, nullptr, hInstance, nullptr);
		}

		void Init(HINSTANCE hInstance)
		{
			MemoryUsageLabel = CreateLabel("Test", 5, 5, hInstance);

			if (!MemoryUsageLabel)
				throw std::exception("Failed to create memory usage label");
		}

		void Update()
		{
			// Update our memory usage label
			SetWindowTextA(Controls::MemoryUsageLabel, std::format("Memory usage: {} percent", Query::Memory::MemoryUsage).c_str());
		}
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		// Terminate the entire process if we close the GUI
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

		// Initialize our controls
		Controls::Init(hInstance);

		MSG Msg = {};

		for (;;)
		{
			// Dispatch messages, update as needed, etc
			while (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&Msg);
				DispatchMessageA(&Msg);
			}

			// Update our controls
			Controls::Update();

			// Only update our window every 150ms
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
}