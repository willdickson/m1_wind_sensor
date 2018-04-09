#include "direction_sensor.h"
#include "constants.h"


DirectionSensor::DirectionSensor()
{ }


void DirectionSensor::initialize(int pin)
{ 
    pin_ = pin;
    pinMode(pin_, INPUT);
}


float DirectionSensor::angle()
{
    return  DegPerRev*voltage()/WindDirectionMaxVolt;
}


float DirectionSensor::voltage()
{
    return AinReferenceVoltage*float(ain_value())/float(AinReadMaxValue);
}


uint16_t DirectionSensor::ain_value()
{ 
    return analogRead(pin_);
}


