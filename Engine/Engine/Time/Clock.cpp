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

void Timing::Clock::start()
{
	QueryPerformanceCounter(&lastStartTime);
}

void Timing::Clock::stop()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - lastStartTime.QuadPart;
	deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;
	deltaLastlap.QuadPart = thisTime.QuadPart;
}

void Timing::Clock::lap()
{
	stop();
	start();
	
}

//float Timing::Clock::timeElapsedLastFrame() const
//{
//	return deltaTime;
//}



float Timing::Clock::lastLapTime() const
{
	return deltaTime;
}

//void Timing::Clock::newFrame()
//{
//	LARGE_INTEGER thisTime;
//	QueryPerformanceCounter(&thisTime);
//	LARGE_INTEGER delta;
//	delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
//	deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;
//	timeLastFrame.QuadPart = thisTime.QuadPart;
//}
