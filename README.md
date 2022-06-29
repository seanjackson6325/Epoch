# Epochness

A high resolution, cross platform time library for C/C++


How to use:

First, the library header must be included:
  
   #include "epochness.h"

Then, the library must be initialized using the following function:

  Epoch_Init();

Now the library is ready to be used.

For high resolution time measurements, use the Epoch_t struct.
The accuracy of these measurements is < 1us.
The Epoch_t struct essentially works as a timer.
Information about the elapsed time can be accessed.
Below is a program that will count to 10 seconds:

  #include <stdio.h>
  #include "epochness.h"

  int main(void)
  {
    // initialize library
	  Epoch_Init();

    // new Epoch_t clock
	  Epoch_t clock;
    // start counting
	  Epoch_Start(&clock);

    // hold elapsed time in seconds
	  double time = 0;
    
    // count to 10 seconds
	  while (time < 10.0)
	  {
      // save elapsed time
		  time = Epoch_QueryChange(&clock);
      // log to console
		  printf("%lf\n", time);
	  }
  }
