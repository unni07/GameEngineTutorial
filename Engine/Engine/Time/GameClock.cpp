#include "GameClock.h"


namespace Timing 
{
	//GameClock::GameClock()
	//{
	//}
	//
	//
	//GameClock::~GameClock()
	//{
	//}

	GameClock GameClock::instance;

	bool GameClock::initialize()
	{
		return clock.initialize();
	}

	bool GameClock::shutdown()
	{
		return clock.shutdown();
	}

	void GameClock::newFrame()
	{
		clock.lap();
	}

	float GameClock::dt() const
	{
		return clock.lastLapTime();
	}

	GameClock& GameClock::getInstance()
	{
		// TODO: insert return statement here
		return instance;
	}

}
