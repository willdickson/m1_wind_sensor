#include "speed_sensor.h"
#include <util/atomic.h>
#include "constants.h"


SpeedSensor::SpeedSensor()
{ 
    curr_pulse_us_ = -1*(WindSpeedPulseTimeout + 1);
    prev_pulse_us_ = -2*(WindSpeedPulseTimeout + 1);
    pulse_dt_us_ = WindSpeedPulseTimeout + 1;
    freq_hz_ = 0.0;
}


void SpeedSensor::initialize(int pin, void(*pin_cb)())
{ 
    pin_ = pin;
    pin_cb_ = pin_cb;

    pinMode(pin_, INPUT);
    attachInterrupt(pin_, pin_cb_, RISING);
}


float SpeedSensor::freq_hz()
{
    return freq_hz_;
}


float SpeedSensor::speed()
{
    return WindSpeedCalibSlope*freq_hz_ + WindSpeedCalibOffset;
}


void SpeedSensor::update_on_loop()
{
    bool timeout = false;
    uint32_t pulse_dt_us = 0;
    uint32_t curr_time_us = micros();


    // Compute pulse dt and check for timeout  
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if ((curr_time_us - curr_pulse_us_) > WindSpeedPulseTimeout)
        {
            timeout = true;
            curr_pulse_us_ = curr_time_us - 1*(WindSpeedPulseTimeout + 1);
            prev_pulse_us_ = curr_time_us - 2*(WindSpeedPulseTimeout + 1);
        }
        pulse_dt_us = curr_pulse_us_ - prev_pulse_us_;
    }
    
    // Compute frequency
    if (timeout) 
    {
        freq_hz_ = 0.0;
    }
    else
    {
        freq_hz_ = 1.0/float(UsecPerSec*pulse_dt_us);
    }

}




