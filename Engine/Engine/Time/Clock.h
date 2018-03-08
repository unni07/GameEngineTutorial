#pragma once
#include <Windows.h>


namespace Timing {
	class __declspec(dllexport) Clock
	{
		LARGE_INTEGER timeLastFrame;
		LARGE_INTEGER timeFrequency;
		LARGE_INTEGER deltaLastlap;

		LARGE_INTEGER lastStartTime;
		float deltaTime;

	public:
		Clock();
		~Clock();

		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap(); //newFrame();
		//float timeElapsedLastFrame() const;
		float lastLapTime() const; //timeElapsedLastLapTime
		//void newFrame();

	};
}

