#ifndef DIRECTION_SENSOR_H
#define DIRECTION_SENSOR_H
#include <Arduino.h>

class DirectionSensor
{
    public:

        DirectionSensor();
        void initialize(int pin);
        float angle();
        float voltage();
        uint16_t ain_value();

    protected:

        int pin_;
};

#endif
