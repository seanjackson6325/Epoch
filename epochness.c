/****************************************************************
*
* Author: Sean Jackson
* Last Modified: 09/05/21
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
	bool Epoch_Init()
	{
		QueryPerformanceFrequency(&epoch_query_frequency);
	}

	// start the epoch
	void Epoch_Start(Epoch_t* e)
	{
		QueryPerformanceCounter(&e->last);
	}

	// get the change in ticks from the last time this function
	// was called (or when the epoch was started if called for the first time)
	double Epoch_QueryChange(Epoch_t* e)
	{
		QueryPerformanceCounter(&e->now);
		epoch_int change = e->now - e->last;
		return (double)change / epoch_query_frequency;
	}

#else

  bool Epoch_Init() {}

  void Epoch_Start(Epoch_t* e)
  {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e->last);
  }

  double Epoch_QueryChange(Epoch_t* e)
	{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &e->now);
    timespec diff;

    if(e->now.tv_nsec - e->last.tv_nsec < 0)
    {
      diff.tv_sec = e->now.tv_sec - e->last.tv_sec-1;
      diff.tv_nsec = 1000000000 + e->now.tv_nsec - e->last.tv_nsec;
    }
    else
    {
      diff.tv_sec = e->now.tv_sec - e->last.tv_sec;
      diff.tv_nsec = e->now.tv_nsec - e->last.tv_nsec;
    }

    return diff.tv_sec + diff.tv_nsec / 1000000000.0;
	}

#endif
