#include "CommonIncludes.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int nShowCmd)
{
	try
	{
#ifdef _DEBUG
		// Allow console debug information
		FILE* Out = nullptr;

		if (!AllocConsole())
			throw std::exception("Failed to allocate console " __FUNCTION__);

		if (freopen_s(&Out, "CONOUT$", "w", stdout) != 0)
			throw std::exception("Failed to open out stream " __FUNCTION__);

		SetConsoleTitleA("Debug Console | HardwareQuery");
#endif

		Query::Init();
		GUI::Init(hInstance, nShowCmd);
	}
	catch (std::exception& exception)
	{
		MessageBoxA(nullptr, exception.what(), "Initialization Error", MB_ICONERROR | MB_OK);
	}
}