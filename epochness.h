/****************************************************************
*
* Author: Sean Jackson
* Last Modified: 06/29/22
* Description: Header for "Epochness" cross-platform time lib
*
****************************************************************/

#pragma once
#include <stdbool.h>

/////////////////////////////////////////////////////////////////

#ifdef _WIN32

	// for time functions:
	#include "windows.h"

  	// type for keeping track of ticks
	typedef unsigned long long epoch_int;

	// struct for epoch:
	typedef struct
	{
		epoch_int last, now;
	} Epoch_t;

/////////////////////////////////////////////////////////////////

#else

	#include <time.h>
	#include <sys/time.h>

	typedef struct timespec timespec;

	typedef struct
	{
		timespec last, now;
	} Epoch_t;

/////////////////////////////////////////////////////////////////

#endif

bool Epoch_Init();
void Epoch_Start(Epoch_t* e);
double Epoch_QueryChange(Epoch_t* e);
