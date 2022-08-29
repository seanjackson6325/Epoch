/****************************************************************
*
* Author: Sean Jackson
* Last Modified: 06/29/22
* Description: Header for "Epochness" cross-platform time lib
*
****************************************************************/

#include "epochness.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////

#ifdef _WIN32

// the tick frequency constant
// (conversion from ticks to seconds)
epoch_int epoch_query_frequency = 0;

// prepare the epochness library for use
// returns 0 on failure
unsigned char Epoch__Init()
{
	return QueryPerformanceFrequency(&epoch_query_frequency);
}

// start the epoch
void Epoch__Start(Epoch_t* e)
{
	QueryPerformanceCounter(&e->last);
}

/*
* Get the change in time (seconds)
* since the timer was started
*/
double Epoch__QueryChange(Epoch_t* e)
{
	QueryPerformanceCounter(&e->now);
	epoch_int change = e->now - e->last;
	return (double)change / epoch_query_frequency;
}

// get system time information
void Epoch__QuerySysInfo(Epoch_SysInfo_t* t, unsigned char type)
{
	SYSTEMTIME systime;
	switch (type)
	{
	case EPOCH_LOCAL_TIME: GetLocalTime(&systime); break;
	default: GetSystemTime(&systime); break;
	}

	*t = (Epoch_SysInfo_t)
	{
		systime.wYear,
		systime.wMonth,
		systime.wDayOfWeek,
		systime.wDay,
		systime.wHour,
		systime.wMinute,
		systime.wSecond,
	};
}

/////////////////////////////////////////////////////////////////

#else

// prepare the epochness library for use
// returns 0 on failure
unsigned char Epoch__Init() { return 1; }

// start the epoch
void Epoch__Start(Epoch_t* e)
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e->last);
}

/*
* Get the change in time (seconds)
* since the timer was started
*/
double Epoch__QueryChange(Epoch_t* e)
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e->now);
	timespec diff;

	if (e->now.tv_nsec - e->last.tv_nsec < 0)
	{
		diff.tv_sec = e->now.tv_sec - e->last.tv_sec - 1;
		diff.tv_nsec = 1000000000 + e->now.tv_nsec - e->last.tv_nsec;
	}
	else
	{
		diff.tv_sec = e->now.tv_sec - e->last.tv_sec;
		diff.tv_nsec = e->now.tv_nsec - e->last.tv_nsec;
	}

	return diff.tv_sec + diff.tv_nsec / 1000000000.0;
}

void Epoch__QuerySysInfo(Epoch_SysTime_t* t, unsigned char type)
{
	time_t now;
	time(&now);

	struct tm* local;

	switch (type)
	{
	case EPOCH_LOCAL_TIME: local = localtime(&now); break;
	default: local = gmtime(&now) break;
	}

	*t = (Epoch_SysTime_t)
	{
		local->tm_year,
		local->tm_mon,
		local->tm_wday
		local->tm_mday,
		local->tm_hour,
		local->tm_min,
		local->tm_sec,
	};
}

/////////////////////////////////////////////////////////////////

#endif