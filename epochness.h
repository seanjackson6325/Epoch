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

#ifdef _WIN32

	// type for keeping track of ticks
	typedef unsigned long long epoch_int;

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
double Epoch_QueryChange(Epoch_t* e);
