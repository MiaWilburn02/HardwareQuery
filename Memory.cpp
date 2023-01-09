#include "CommonIncludes.h"

namespace Query
{
	namespace Memory
	{
		MEMORYSTATUSEX MemStatus;
		DWORDLONG TotalMemory;
		DWORD MemoryUsage;

		void Init()
		{
			MemStatus.dwLength = sizeof(MEMORYSTATUSEX);

			// Get our memory status
			if (!GlobalMemoryStatusEx(&MemStatus))
				throw std::exception("GlobalMemoryStatus Failed " __FUNCTION__);

			// Remember, this is bytes!
			TotalMemory = MemStatus.ullTotalPhys;

			if (!(TotalMemory > 0))
				throw std::exception("We think we have no memory " __FUNCTION__);
		}

		void Thread()
		{
			for (;;)
			{
				// Update our memory status
				GlobalMemoryStatusEx(&MemStatus);

				// Store our used memory, luckily this already stores in a
				// percentage format for us [0..100]
				MemoryUsage = MemStatus.dwMemoryLoad;

#ifdef _DEBUG
				// Print debug information about our memory
				printf_s("MEMORY UPDATE!\n");
				printf_s("Memory Usage: %i Percent\n", MemoryUsage);
#endif
				std::this_thread::sleep_for(std::chrono::milliseconds(UpdateDelayMs));
			}
		}
	}
}