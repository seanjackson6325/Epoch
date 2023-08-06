# Epoch

Epoch is a high resolution, cross platform time library for C/C++.
This library can provide time measurements of less than one microsecond (1E-6 seconds),
as well as date and time information in local and UTC time.





## Data types:



#### Epoch_t

- Essentially acts as a timer to hold elapsed time info


#### Epoch_SysInfo_t

- Holds current system time information.

	    typedef struct
	    {
		unsigned short year;
		unsigned short month;
		unsigned short weekday;
		unsigned short day;
		unsigned short hour;
		unsigned short minute;
		unsigned short second;
	    } Epoch_SysInfo_t;
    



## Constants:


#### EPOCH_LOCAL_TIME

- Used to query system time information in local time (the local time in your area).


#### EPOCH_UTC_TIME

- Used to query system time information in universal coordinated time (UTC).




## Functions:


#### unsigned char Epoch__Init();
- Intializes internal variables for use. Needs to be called only once at the start of the program.

  
#### void Epoch__Start(Epoch_t*);
- Initializes an Epoch_t and resets it's elapsed time. This must be called to start an Epoch_t before it's elapsed time is ever queried.


#### double Epoch__QueryChange(Epoch_t*);
- Gets the elapsed time from an Epoch_t.

  
#### void Epoch__QuerySysInfo(Epoch_SysInfo_t*, unsigned char type);
- Fill a Epoch_SysInfo_t with system time information. "type" should be either EPOCH_LOCAL_TIME or EPOCH_UTC_TIME.


## Examples:

#### Run a loop for five seconds
	#include <stdio.h>
	#include "epoch.h"
	
	int main(int argc, char* argv[])
	{
	    // Initialize Epoch
	    Epoch__Init();
	
	    // Create a new timer
	    Epoch_t timer;
	
	    // Start the timer
	    Epoch__Start(&timer);
	    // Keep track of elapsed time
	    double elapsed;
	
	    // Print out elapsed time
	    // for five seconds
	    do
	    {
	        // Get change in time since the
	        // timer was started
	        elapsed = Epoch__QueryChange(&timer);
	        printf("%f\n", elapsed);
	    }
	    while (elapsed < 5.0);
	
	    // Used to hold system information
	    Epoch_SysInfo_t info;
	
	    // Get current system information (local time)
	    Epoch__QuerySysInfo(&info, EPOCH_LOCAL_TIME);
	
	    // Print some info
	    printf("Current Year: %d\n", info.year);
	    printf("Current Month (0-11): %d\n", info.month);
	    printf("Current Weekday (0-6): %d\n", info.weekday);
	    printf("Current Day (0-355): %d\n", info.day);
	    printf("Current Hour (0-23): %d\n", info.hour);
	    printf("Current Minute (0-59): %d\n", info.minute);
	    printf("Current Second (0-60): %d\n", info.second);
	}
