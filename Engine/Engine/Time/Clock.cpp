#include "Clock.h"


using namespace Timing;

Clock::Clock()
{
}


Clock::~Clock()
{
}

bool Timing::Clock::initialize()
{
	bool b = QueryPerformanceFrequency(&timeFrequency);
	if (!b)
		return false;
	b = QueryPerformanceCounter(&timeLastFrame);

	return b;
}

bool Timing::Clock::shutdown()
{
	return true;
}

float Timing::Clock::timeElapsedLastFrame() const
{
	return deltaTime;
}

void Timing::Clock::newFrame()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
	deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;
	timeLastFrame.QuadPart = thisTime.QuadPart;
}
