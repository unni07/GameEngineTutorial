#include "profiler.h"

#ifdef PROFILING_ON
#include <cassert>
#include <fstream>
#endif

namespace Profiling
{


	Profiler Profiler::theInstance;
	Profiler & Profiler::getInstance()
	{
		// TODO: insert return statement here
		return theInstance;
	}
	
#ifdef PROFILING_ON
	static std::ofstream outStream;

	Profiler::~Profiler()
	{
	}

	void Profiler::initialize(const char* filename)
	{
		this->fileName = filename;
		frameIndex = -1;
		categoryIndex = 0;
		status = true;
		numUsedCategories = 0;
		temp = 10;
	}

	void Profiler::addEntry(const char * category, float time)
	{
		//assert(frameIndex < MAX_FRAME_SAMPLES);
		assert(categoryIndex < MAX_PROFILE_CATEGORIES);
		ProfileCategory& pc = categories[categoryIndex];
		if (frameIndex == 0)
		{
			pc.name = category;
			numUsedCategories++;
			checkForDuplicateCategory(category);
		
		}
		else
		{
			//assert(strcmp(category , pc.name) == 0);
			assert(category == pc.name && category != NULL);
			assert(categoryIndex < numUsedCategories);
		}
		categoryIndex++;
		pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;

	}



	void Profiler::newFrame()
	{
		assert(status);
		if (frameIndex > 0)
			assert(categoryIndex == numUsedCategories);

		frameIndex++;
		categoryIndex = 0;
	}

	void Profiler::shutdown()
	{
		writeData();

	}


	void Profiler::writeData() const
	{
		outStream.open(fileName);

		//write category headers
		for (JE::uint i = 0; i < numUsedCategories; i++)
		{
			outStream << categories[i].name;
			char c = ((i + 1) < numUsedCategories) ? ',' : '\n';
			outStream << getDeliminator(i);
			/*	if ((i + 1) < numUsedCategories)
			outStream << ',';
			else
			outStream << '\n';*/
		}

		JE::uint numActualFrame = frameIndex;
		if (currentFrameComplete())
			numActualFrame++;

		JE::uint endIndex;
		JE::uint startIndex;
		if (wrapped())
		{
			endIndex = frameIndex % MAX_FRAME_SAMPLES;
			startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
			while (startIndex != endIndex)
			{
				writeFrame(startIndex);
				startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
			}
			if (currentFrameComplete())
				writeFrame(startIndex);
		}
		else
		{
			endIndex = numActualFrame;
			startIndex = 0;
			while (startIndex < endIndex)
			{
				writeFrame(startIndex++);
			}
		}
		outStream.close();
	}

	void Profiler::writeFrame(JE::uint frameNumber) const
	{
		for (JE::uint cat = 0; cat < numUsedCategories; cat++)
		{
			const ProfileCategory& p = categories[cat];
			outStream << categories[cat].samples[frameNumber];
			outStream << getDeliminator(cat);
		}
	}

	bool Profiler::wrapped() const
	{
		return frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
	}

	bool Profiler::currentFrameComplete() const
	{
		return categoryIndex == numUsedCategories;
		;
	}

	const char Profiler::getDeliminator(JE::uint index) const
	{
		return (((index + 1) < numUsedCategories) ? ',' : '\n');;
	}

	void Profiler::checkForDuplicateCategory(const char * category)
	{

		for (int i = 0; i < categoryIndex; i++)
			status &= (strcmp(categories[0].name, category) != 0);
	}

	void Profiler::checkStatus(bool * status) const
	{
		*status = this->status;
	}

#endif
}
