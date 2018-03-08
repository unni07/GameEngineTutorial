#include <gtest\gtest.h>
#include <Debug Tools\Profiling\profiler.h>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;
using JE::uint;
using Profiling::Profiler;
namespace
{
	const char* const profileFileName = "profile.csv";

	char* categories[] = {
		"Category1",
		"Category2",
		"Category3"
	};
	//const unsigned int NUM_FRAMES = 5;
	const unsigned int NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);
	//Profiler profiler;
}


string getNextToken(ifstream& theFile)
{
	char c,d = '-';
	string ret;
	while (theFile.good())
	{
		theFile >> std::noskipws;
		theFile >> c;
		if (c == ',' || d == '\n')
		{
			/*if (d == '\n')
				theFile >> d;*/
			break;
		}
		d = theFile.peek();
		ret += c;
	}
	return ret;
}

void writeFrames(unsigned int numFrames)
{
	int sampleFrame = 0;
	for (unsigned int frame = 0; frame < numFrames; frame++)
	{
		profiler.newFrame();
		for (int cat = 0; cat<NUM_CATEGORIES; cat++)
			profiler.addEntry(categories[cat], sampleFrame++);
	}
}

bool isAtEndOfFile(ifstream& input)
{
	if (!input.good())
		return false;
	char bitBucket;
	input >> bitBucket;

	return !input.good();
}

void checkFrames(unsigned int numFrames, bool excludeLastFrame = false)
{
	ifstream input(profileFileName);
	for (unsigned int i = 0; i < NUM_CATEGORIES; i++)
	{
		EXPECT_EQ(getNextToken(input), categories[i]);
	}
	unsigned int profileNumber = 0;
	unsigned int framesInRAM = numFrames;
	if (numFrames >= Profiler::MAX_FRAME_SAMPLES)
	{
		profileNumber = (numFrames - Profiler::MAX_FRAME_SAMPLES) * NUM_CATEGORIES;
		framesInRAM = Profiler::MAX_FRAME_SAMPLES;
	}
	if (excludeLastFrame)
	{
		profileNumber += NUM_CATEGORIES * 1;// 1 indicates the frame that needs to be excluded
											// if 1 is to be changed to any number then that number of frames will be excluded
		framesInRAM--;
	}
	for (int i = 0; i < framesInRAM * NUM_CATEGORIES; i++)
	{
		string buf = getNextToken(input);
		int val = atoi(buf.c_str());
		EXPECT_EQ(val, profileNumber++);
	}
	EXPECT_TRUE(isAtEndOfFile(input));
}

void runTestsOnFrames(unsigned int Frames)
{
	profiler.initialize(profileFileName);
	writeFrames(Frames);
	profiler.shutdown();
	checkFrames(Frames);
}

//TEST(Profiler, init)
//{
//
//	profiler.initialize(profileFileName);
//	const unsigned int NUM_FRAMES_THIS_TEST = Profiler::MAX_FRAME_SAMPLES;
//	writeFrames(NUM_FRAMES_THIS_TEST);
//	profiler.shutdown();
//	checkFrames(NUM_FRAMES_THIS_TEST);
//	
//}

void writeIncompleteFrames(unsigned int numFrames)
{
	bool wrapped = numFrames >= Profiler::MAX_FRAME_SAMPLES;
	profiler.initialize(profileFileName);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 15);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);


	profiler.initialize(profileFileName);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 15);
	profiler.addEntry(categories[1], 16);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);
}

//TEST(Profiler, ExcludeIncompleteFrames)
//{
//	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES - 2);
//	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES + 2);
//
//}
//
//TEST(Profiler, smallAmountOfFrames)
//{
//	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES * 0.2f);
//}
//
//TEST(Profiler, largeAmountOfFramesNonCircular)
//{
//	const unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * 0.8f);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
//}
//
//TEST(Profiler, ArrayBoundaries)
//{
//
//	unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST + 1);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST + 2);
//}
//
//TEST(Profiler, CirculatingOnePlusSome)
//{
//	const unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * 1.5);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
//
//}
//
//TEST(Profiler, GoArroundSeveralTimes)
//{
//	const unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES *3.2);
//	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
//
//}

TEST(Profile, AddingDuplicateCategoriesInOneFrame)
{
	profiler.initialize(profileFileName);
	profiler.newFrame();
	profiler.addEntry("My First Category", 1);
	profiler.addEntry("My Second Category", 2);
	bool status;
	profiler.checkStatus(&status);

	EXPECT_TRUE(status);
	profiler.addEntry("My First Category", 2);
	profiler.checkStatus(&status);
	EXPECT_TRUE(!status);
	profiler.shutdown();
}