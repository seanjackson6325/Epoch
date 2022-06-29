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

// the tick frequency constant
// (conversion from ticks to seconds)
epoch_int epoch_query_frequency = 0;

#ifdef WIN32
	
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
	epoch_int Epoch_QueryChange(Epoch_t* e)
	{
		QueryPerformanceCounter(&e->now);
		epoch_int change = e->now - e->last;
		e->last = e->now;
		return change;
	}

	// return the tick frequency constant
	epoch_int Epoch_TicksPerSecond()
	{
		return epoch_query_frequency;
	}

	// convert from ticks to seconds
	double Epoch_TicksToSeconds(epoch_int ticks)
	{
		return (double)ticks / epoch_query_frequency;
	}

	void Epoch_GameLoop(bool* run, const int UPS, void(update)(void), void(render)(void), char* report_buff)
	{
		Epoch_t clock;
		Epoch_Start(&clock);

		double d_ticks = 0.0;
		double TPS = (double)Epoch_TicksPerSecond();
		double TPU = TPS / UPS;

		int ups = 0;
		int fps = 0;
		double report = 0.0;

		while (*run)
		{
			epoch_int delta = Epoch_QueryChange(&clock);
			d_ticks += (double) delta;
			report += (double) delta;
			if (d_ticks >= TPU)
			{
				d_ticks -= TPU;
				update();
				ups++;
			}
			render();
			fps++;

			if (report >= TPS)
			{
				report -= TPS;
				printf("UPS:%d\tFPS:%d\n", ups, fps);
				fps = ups = 0.0;
			}
		}
	}

#else
// TODO: WRITE LINUX VERSION HERE
#endif