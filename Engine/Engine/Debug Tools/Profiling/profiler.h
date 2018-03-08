#pragma once
#include <Misc\TypeDefs.h>

namespace Profiling 
{
	class __declspec(dllexport) Profiler
	{
	public:

		static const JE::uint MAX_FRAME_SAMPLES = 1000;
		~Profiler();
		static Profiler& getInstance();

#if PROFILING_ON
		void addEntry(const char * category, float time);
		void initialize(const char* filename);
		void newFrame();
		void shutdown();
		void checkStatus(bool* status) const;
#else
		void addEntry(const char * category, float time) {}
		void initialize(const char* filename) {}
		void newFrame() {}
		void shutdown() {}
		void checkStatus(bool* status) const {}
#endif

	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;

#if PROFILING_ON
		const char * fileName;
		static const JE::uint MAX_PROFILE_CATEGORIES = 20;
		int frameIndex;
		bool status;
		JE::uint categoryIndex;
		JE::uint numUsedCategories;
		void writeData() const;
		void writeFrame(JE::uint frameNumber) const;
		bool wrapped() const;
		bool currentFrameComplete() const;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		}categories[MAX_PROFILE_CATEGORIES];
		const char getDeliminator(JE::uint)const;
		void checkForDuplicateCategory(const char * category);
		int temp;
#endif
	};


}
#define profiler Profiling::Profiler::getInstance()
