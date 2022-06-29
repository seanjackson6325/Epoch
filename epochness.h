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

// timespec holds seconds and nanoseconds
typedef struct timespec timespec;

// struct for epoch:
typedef struct
{
	timespec last, now;
} Epoch_t;

/////////////////////////////////////////////////////////////////

#endif

// initialize epochness
bool Epoch_Init();
// start an epoch timer
void Epoch_Start(Epoch_t* e);
// return time (seconds) since start
double Epoch_QueryChange(Epoch_t* e);

/////////////////////////////////////////////////////////////////
