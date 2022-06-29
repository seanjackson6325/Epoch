/****************************************************************
*
* Author: Sean Jackson
* Last Modified: 09/05/21
* Description: Header for "Epochness" cross-platform time lib
*
****************************************************************/

#pragma once
#include <stdbool.h>

/////////////////////////////////////////////////////////////////

// type for keeping track of ticks
typedef unsigned long long epoch_int;

#ifdef WIN32

	// for time functions:
	#include "windows.h"

	// struct for epoch:
	typedef struct
	{
		epoch_int last, now;
	} Epoch_t;

/////////////////////////////////////////////////////////////////

#else
	#include "time.h"
	// TODO: WRITE LINUX IMPLEMENTATION HERE

/////////////////////////////////////////////////////////////////

#endif


bool Epoch_Init();
void Epoch_Start(Epoch_t* e);
epoch_int Epoch_QueryChange(Epoch_t* e);
epoch_int Epoch_TicksPerSecond();
double Epoch_TicksToSeconds(epoch_int ticks);
void Epoch_GameLoop(bool* run, const int UPS, void(update)(void), void(render)(void), char* report_buff);