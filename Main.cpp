#include "CommonIncludes.h"

int main()
{
	try
	{
		Query::Init();
	}
	catch (std::exception& exception)
	{
		MessageBoxA(nullptr, exception.what(), "Initialization Error", MB_ICONERROR | MB_OK);
	}

	for (;;)
	{

	}
}