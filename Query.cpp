#include "CommonIncludes.h"

namespace Query
{
	int UpdateDelayMs;

	void Init()
	{
		// By default, only update every second
		UpdateDelayMs = 1000;

		// Initialize all of our hardware queries
		Memory::Init();

		// Create all of our threads
		std::thread MemoryThread(Memory::Thread);
		MemoryThread.detach();
	}
}