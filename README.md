# Epoch

Epoch is a high resolution, cross platform time library for C/C++.
This library can provide time measurements of less than one microsecond (1E-6 seconds),
as well as date and time information in local and UTC time.


Functions and data types:

initialize epochness
  unsigned char Epoch__Init();
  
  // start an epoch timer
  void Epoch__Start(Epoch_t* e);
  
  // return float time (seconds) since start
  double Epoch__QueryChange(Epoch_t* e);
  
  // return system date and time information
  // for type, use either EPOCH_LOCAL_TIME or EPOCH_UTC_TIME
  void Epoch__QuerySysInfo(Epoch_SysInfo_t* t, unsigned char type);
