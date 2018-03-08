#pragma once
#include <Time\Clock.h>

namespace Timing
{
	class __declspec(dllexport) GameClock
	{
		Clock clock;
		GameClock() {}
		GameClock(const GameClock&);
		GameClock& operator= (const GameClock&);
		static GameClock instance;

	public:
		bool initialize();
		bool shutdown();
		void newFrame();
		float dt() const;
		static GameClock& getInstance();
		/*~GameClock();*/
	};
#define gameClock Timing::GameClock::getInstance()
}

