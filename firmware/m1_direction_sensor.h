#ifndef DIRECTION_SENSOR_H
#define DIRECTION_SENSOR_H
#include <Arduino.h>
#include "constants.h"

template<int TPin>
class M1DirectionSensor
{
    public:

        static void initialize();
        static float angle();
        static float voltage();
        static uint16_t ain_value();

    private:

        M1DirectionSensor() {};

};

template<int TPin>
void M1DirectionSensor<TPin>::initialize()
{
    pinMode(TPin, INPUT);
}

template<int TPin>
float M1DirectionSensor<TPin>::angle()
{
    return  DegPerRev*voltage()/WindDirectionMaxVolt;
}

template<int TPin>
float M1DirectionSensor<TPin>::voltage()
{
    return AinReferenceVoltage*float(ain_value())/float(AinReadMaxValue);
}

template<int TPin>
uint16_t M1DirectionSensor<TPin>::ain_value()
{
    return analogRead(TPin);
}


#endif
