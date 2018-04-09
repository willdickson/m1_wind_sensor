#include "constants.h"

const float DegPerRev = 360.0;
const float UsecPerSec = 1.0e-6;
const uint32_t LoopDelayDtMS= 2;

const int Baudrate = 115200;
extern const int AngleSendDigits = 1; 
extern const int SpeedSendDigits = 3;
const uint32_t SendTimerPeriodUS = 50000;

// Analog input parameters
const int AinReadResolution = 16;
const int AinReadAveraging = 16;
const float AinReferenceVoltage = 3.3;
const uint32_t AinReadMaxValue = (1<<AinReadResolution) - 1;

// Wind direction sensor parameters
const float WindDirectionMaxVolt = 2.4894;

// Wind speed sensor parameters
const float WindSpeedCalibSlope = 0.039976;
const float WindSpeedCalibOffset = 0.27;
const uint32_t WindSpeedPulseTimeout = 2000000;
