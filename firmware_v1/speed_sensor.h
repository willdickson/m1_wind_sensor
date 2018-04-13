#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H
#include <Arduino.h>

class SpeedSensor
{
    public:

        SpeedSensor();
        void initialize(int pin, void(*pin_cb)());

        void update_on_loop();
        inline void update_on_pin();

        float freq_hz();
        float speed();

    protected:

        int pin_;

        volatile uint32_t curr_pulse_us_;
        volatile uint32_t prev_pulse_us_;
        uint32_t pulse_dt_us_;
        float freq_hz_;

        void (*pin_cb_)() = dummy_cb_;
        static void dummy_cb_() {};

};

inline void SpeedSensor::update_on_pin()
{
    prev_pulse_us_ = curr_pulse_us_;
    curr_pulse_us_ = micros();
}

#endif
