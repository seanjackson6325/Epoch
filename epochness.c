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
		e->last = e->now;
		return (double)change / epoch_query_frequency;
	}

#else
// TODO: WRITE LINUX VERSION HERE
#endif
