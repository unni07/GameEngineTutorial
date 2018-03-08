#pragma once
#include <Windows.h>


namespace Timing {
	class __declspec(dllexport) Clock
	{
		LARGE_INTEGER timeLastFrame;
		LARGE_INTEGER timeFrequency;
		float deltaTime;

	public:
		Clock();
		~Clock();

		bool initialize();
		bool shutdown();
		float timeElapsedLastFrame() const;
		void newFrame();

	};
}

