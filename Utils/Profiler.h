#ifndef _PROFILER_H_
#define _PROFILER_H_

#include <vector>
#include <map>
#include <string>
#include "Timer.h"

class ProfilerSubscriber
{
public:
	// sends the name and time
	virtual void Dump(const char*, float) = 0;
};

class Profiler
{
public:
	void Start(const char* name);
	void End(const char* name);
	void EndDump(const char* name); // ends profile and immediately dumps this message only
	void Dump();
	void Subscribe(ProfilerSubscriber& sub);

private:
	std::vector<ProfilerSubscriber*> _subscribers;
	std::map<std::string, Timer> _currentprofiles;
	std::map<std::string, float> _finishedprofiles;
};

static Profiler MainProfiler;

#define ProfileStart(name) MainProfiler.Start(name)
#define ProfileEnd(name) MainProfiler.End(name)
#define ProfileEndDump(name) MainProfiler.Dump(name)
#define ProfileDump() MainProfiler.Dump()

#endif