#include "Profiler.h"
#include <string>

void Profiler::Start(const char* name)
{
	_currentprofiles[name] = Timer();
};

void Profiler::End(const char* name)
{
	auto it = _currentprofiles.find(name);

	// if not found
	if (it == _currentprofiles.end())
		return;

	_finishedprofiles[name] = it->second.GetSeconds();
	_currentprofiles.erase(it);
};

void Profiler::EndDump(const char* name)
{
	auto it = _currentprofiles.find(name);

	// if not found
	if (it == _currentprofiles.end())
		return;
	
	for (auto sub : _subscribers)
		sub->Dump(name, it->second.GetSeconds());

	_currentprofiles.erase(it);
};

void Profiler::Dump()
{
	for (auto entry : _finishedprofiles)
	{
		for (auto sub : _subscribers)
			sub->Dump(entry.first.c_str(), entry.second);
	}

	_finishedprofiles.clear();
};

void Profiler::Subscribe(ProfilerSubscriber& sub)
{
	_subscribers.push_back(&sub);
};