#include <gtest\gtest.h>
#include <QT\qTest.h>
#include <Time\Clock.h>

using Timing::Clock;

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	QTest::qSleep(1000);
	clock.newFrame();
	//EXPECT_FLOAT_EQ(clock.timeElapsedLastFrame(), 0.0f);

	float timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.9f < timedTime);
	EXPECT_TRUE(timedTime < 1.1f);
	clock.newFrame();
	QTest::qSleep(500);
	clock.newFrame();
	timedTime = clock.timeElapsedLastFrame();
	EXPECT_TRUE(0.4f < timedTime);
	EXPECT_TRUE(timedTime < 0.6f);
	
	const int numTest = 10 + rand() % 2;
	const float THRESHOLD = 0.001f;
	for (int i = 0; i < numTest; i++)
	{
		int thisTestMilisec = 100 + rand() % 10000;
		float thisTestSeconds = thisTestMilisec / 1000.0f;
		clock.newFrame();
		QTest::qSleep(thisTestMilisec);
		clock.newFrame();
		float elapsedSeconds = clock.timeElapsedLastFrame();// / 1000.0f;
		//std::cout << "Frame " << i << "\t" << thisTestMilisec<<std::endl;
		EXPECT_TRUE((thisTestSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE(elapsedSeconds < (thisTestSeconds + THRESHOLD));

	}

	clock.newFrame();
	clock.timeElapsedLastFrame();
	EXPECT_TRUE(clock.shutdown());
}