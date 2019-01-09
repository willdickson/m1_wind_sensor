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
        static float getFakeDirection();

};

template<int TPin>
void M1DirectionSensor<TPin>::initialize()
{
    pinMode(TPin, INPUT);
}

template<int TPin>
float M1DirectionSensor<TPin>::angle()
{
#ifdef DEVELOP_SEND_FAKE_DATA
    return getFakeDirection();
#else
    return  DegPerRev*voltage()/WindDirectionMaxVolt;
#endif
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

template<int TPin>
float M1DirectionSensor<TPin>::getFakeDirection()
{
    static float fake_direction = 0.0;
    fake_direction += random(-100,100)/100.0;
    if (fake_direction < 0)
    {
        fake_direction = fake_direction + 360;
    }
    if (fake_direction >= 360)
    {
        fake_direction =  fake_direction - 360;
    }
    return fake_direction;
}


#endif
