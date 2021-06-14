#include "Log.h"
#include <algorithm>

void LogManager::Write(LogLevel level, const char* msg)
{
	float seconds = _timer.GetSeconds();
	for (auto s : _subscribers)
		s->Write(seconds, level, msg);
};

void LogManager::Subscribe(LogSubscriber& subscriber)
{
	_subscribers.push_back(&subscriber);
};

bool LogManager::Unsubscribe(LogSubscriber& subscriber)
{
	auto it = std::find(_subscribers.begin(), _subscribers.end(), &subscriber);
	if (it == _subscribers.end())
		return false;
	_subscribers.erase(it);
	return true;
};

bool LogFile::SetFile(const char* filename)
{
	if (_file)
		_file.close();
	_file.open(filename, std::ofstream::out | std::ofstream::trunc);
	return _file.is_open();
};

void LogFile::Write(float time, LogLevel level, const char* msg)
{
	if (!_file)
		return;
	_file << time << "\t" << LogLevelStrings[level] << "\t" << msg << std::endl; // auto-flush
};