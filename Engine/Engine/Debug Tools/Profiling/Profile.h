#pragma once
#if PROFILING_ON
#include<Time\Clock.h>
#endif

namespace Profiling
{
	class __declspec(dllexport) Profile
	{
#if PROFILING_ON
		Timing::Clock clock;
		const char* category;
#endif
	public:
#if PROFILING_ON
		Profile(const char* category);
		~Profile();
#else
		Profile(const char* category)
		{

		}
		~Profile()
		{}
#endif
	};
}
#if PROFILING_ON
#define PROFILE(category) Profiling::Profile p(category)
#else
#define PROFILE(category)
#endif
