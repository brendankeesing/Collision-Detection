#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer();

	float GetSeconds();
	long long GetTicks();
	bool Reset();

private:
	long long Before;
	long long Frequency;
};

#endif