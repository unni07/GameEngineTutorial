#if PROFILING_ON
#include"profile.h"
#include "Debug Tools\Profiling\profiler.h"
namespace  Profiling
{
	Profile::Profile(const char * category):category(category)
	{
		clock.initialize();
		clock.start();
	}

	Profile::~Profile()
	{
		clock.stop();
		//profiler.newFrame();
		profiler.addEntry(category, clock.lastLapTime());
	}
}
#endif
