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
//#define OVERNIGHT_TESTS
#ifdef OVERNIGHT_TESTS
	EXPECT_TRUE(clock.initialize());
	clock.start();
	QTest::qSleep(1000);
	clock.stop();
	//clock.lap();
	//EXPECT_FLOAT_EQ(clock.lastLapTime(), 0.0f);

	float timedTime = clock.lastLapTime();
	EXPECT_TRUE(0.9f < timedTime);
	EXPECT_TRUE(timedTime < 1.1f);
	//clock.lap();
	clock.start();
	QTest::qSleep(500);
	clock.stop();
	//clock.lap();
	timedTime = clock.lastLapTime();
	EXPECT_TRUE(0.4f < timedTime);
	EXPECT_TRUE(timedTime < 0.6f);
	
	const int numTest = 10 + rand() % 2;
	const float THRESHOLD = 0.01f;
	for (int i = 0; i < numTest; i++)
	{
		int thisTestMilisec = 100 + rand() % 10000;
		float thisTestSeconds = thisTestMilisec / 1000.0f;
		clock.start();
		QTest::qSleep(thisTestMilisec);
		clock.stop();
		float elapsedSeconds = clock.lastLapTime();// / 1000.0f;
		//std::cout << "Frame " << i << "\t" << thisTestMilisec<<std::endl;
		EXPECT_TRUE((thisTestSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE(elapsedSeconds < (thisTestSeconds + THRESHOLD));

	}
#endif
	clock.lap();
	EXPECT_TRUE(clock.shutdown());
}

//
//#include <gtest\gtest.h>
//#include <QT\qTest.h>
//#include <Time\Clock.h>
//
//using Timing::Clock;
//
//TEST(Clock, Initialize)
//{
//	Clock clock;
//	EXPECT_TRUE(clock.initialize());
//	EXPECT_TRUE(clock.shutdown());
//}
//
//TEST(Clock, FrameTimeMeasuring)
//{
//	Clock clock;
//#define OVERNIGHT_TESTS
//#ifdef OVERNIGHT_TESTS
//	EXPECT_TRUE(clock.initialize());
//	clock.lap();
//	QTest::qSleep(1000);
//	clock.lap();
//	float timedTime = clock.lastLapTime();
//	EXPECT_TRUE(0.9f < timedTime);
//	EXPECT_TRUE(timedTime < 1.1f);
//	clock.lap();
//	QTest::qSleep(500);
//	clock.lap();
//	//clock.lap();
//	timedTime = clock.lastLapTime();
//	EXPECT_TRUE(0.4f < timedTime);
//	EXPECT_TRUE(timedTime < 0.6f);
//
//	const int numTest = 10 + rand() % 2;
//	const float THRESHOLD = 0.001f;
//	for (int i = 0; i < numTest; i++)
//	{
//		int thisTestMilisec = 100 + rand() % 10000;
//		float thisTestSeconds = thisTestMilisec / 1000.0f;
//		//clock.lap();
//		clock.lap();
//		QTest::qSleep(thisTestMilisec);
//		clock.lap();
//		//clock.lap();
//		float elapsedSeconds = clock.lastLapTime();// / 1000.0f;
//												   //std::cout << "Frame " << i << "\t" << thisTestMilisec<<std::endl;
//		EXPECT_TRUE((thisTestSeconds - THRESHOLD) < elapsedSeconds);
//		EXPECT_TRUE(elapsedSeconds < (thisTestSeconds + THRESHOLD));
//
//	}
//#endif
//	clock.lap();
//	EXPECT_TRUE(clock.shutdown());
//}