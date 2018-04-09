#ifndef WIND_SENSOR_H
#define WIND_SENSOR_H
#include "direction_sensor.h"
#include "speed_sensor.h"
#include <Arduino.h>


class WindSensor
{
    public:

        WindSensor();
        void initialize(void(*interval_timer_cb)(), void(*speed_sensor_pin_cb)());

        void update_on_loop();
        void send_data();

        inline void update_on_timer();
        inline void update_on_speed_sensor_pin();


    protected:

        SpeedSensor speed_sensor_;
        DirectionSensor direction_sensor_;

        IntervalTimer interval_timer_;
        volatile bool send_flag_;
        
        void (*interval_timer_cb_)() = dummy_cb_;
        static void dummy_cb_() {};
};


inline void WindSensor::update_on_timer()
{
    send_flag_ = true;
}

inline void WindSensor::update_on_speed_sensor_pin()
{
    speed_sensor_.update_on_pin();
}


#endif

