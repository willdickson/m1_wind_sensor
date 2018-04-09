#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <Arduino.h>

extern const float DegPerRev;
extern const float UsecPerSec;
extern const uint32_t LoopDelayDtMS;

// Communication parameters
extern const int Baudrate;
extern const int AngleSendDigits; 
extern const int SpeedSendDigits;
extern const uint32_t SendTimerPeriodUS;

// Analog input parameters
extern const int AinReadResolution;
extern const int AinReadAveraging;
extern const float AinReferenceVoltage;
extern const uint32_t AinReadMaxValue;

// Wind direction sensor parameters
extern const float WindDirectionMaxVolt;

// Wind speed sensor parameters 
extern const float WindSpeedCalibSlope;
extern const float WindSpeedCalibOffset;
extern const uint32_t WindSpeedPulseTimeout;


#endif
