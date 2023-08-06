# Epoch

Epoch is a high resolution, cross platform time library for C/C++.
This library can provide time measurements of less than one microsecond (1E-6 seconds),
as well as date and time information in local and UTC time.





## Data types:



### Epoch_t

- Essentially acts as a timer to hold elapsed time info


### Epoch_SysInfo_t

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


### EPOCH_LOCAL_TIME

- Used to query system time information in local time (the local time in your area).


### EPOCH_UTC_TIME

- Used to query system time information in universal coordinated time (UTC).




## Functions:


### unsigned char Epoch__Init();

  
### void Epoch__Start(Epoch_t*);


### double Epoch__QueryChange(Epoch_t*);

  
### void Epoch__QuerySysInfo(Epoch_SysInfo_t*, unsigned char type);
