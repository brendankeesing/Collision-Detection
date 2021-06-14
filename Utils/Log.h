#ifndef _LOG_H_
#define _LOG_H_

#include <vector>
#include "Timer.h"
#include <fstream>

enum LogLevel
{
	LL_MESSAGE = 0,
	LL_WARNING = 1,
	LL_ERROR = 2
};

static const char* const LogLevelStrings[3] =
{
	"MESSAGE",
	"WARNING",
	"ERROR"
};

class LogSubscriber
{
public:
	virtual void Write(float, LogLevel, const char*) = 0;
};

// Publisher of log messages
// Use MainLog for global logs
class LogManager
{
public:
	LogManager() { _timer.Reset(); };
	void Write(LogLevel level, const char* msg);
	void Write(LogLevel level, std::string& msg) { Write(level, msg.c_str()); };
	void Subscribe(LogSubscriber& subscriber);
	bool Unsubscribe(LogSubscriber& subscriber);

	static LogManager& GetGlobalLog()
	{
		static LogManager globallog;
		return globallog;
	};

private:
	std::vector<LogSubscriber*> _subscribers;
	Timer _timer;
};

// Writes log messages to a file
class LogFile : public LogSubscriber
{
public:
	LogFile() {};
	LogFile(const char* filename) { SetFile(filename); };

	bool SetFile(const char* filename);
	void Write(float time, LogLevel level, const char* msg);

private:
	std::ofstream _file;
};


// Helper macros

// Non-critical information of system status
#define LOG_MESSAGE(msg) LogManager::GetGlobalLog().Write(LogLevel::LL_MESSAGE, msg)

// Recoverable problem or temporary error
#define LOG_WARNING(msg) LogManager::GetGlobalLog().Write(LogLevel::LL_WARNING, msg)

// Critical non-recoverable error
#define LOG_ERROR(msg) LogManager::GetGlobalLog().Write(LogLevel::LL_ERROR, msg)

#define LOG_SUBSCRIBE(subscriber) LogManager::GetGlobalLog().Subscribe(subscriber)
#define LOG_UNSUBSCRIBE(subscriber) LogManager::GetGlobalLog().Unsubscribe(subscriber)

#endif