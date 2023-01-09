#pragma once

namespace Query
{
	namespace Memory
	{
		extern DWORDLONG TotalMemory;
		extern DWORD MemoryUsage;

		void Init();
		void Thread();
	}
}