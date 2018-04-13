#ifndef SPEED_SENSOR_H
#define SPEED_SENSOR_H
#include <Arduino.h>
#include <util/atomic.h>
#include "constants.h"


template<int TPin>
class M1SpeedSensor
{
    public:

        static void initialize();
        static float freq_hz();
        static float speed();

        static void update_on_loop();
        static inline void update_on_pin();

    protected:

        static const uint32_t CurrPulseTimeoutVal_us_;
        static const uint32_t PrevPulseTimeoutVal_us_;
        static const uint32_t PulseDtTimeoutVal_us_;

        static volatile uint32_t curr_pulse_us_;
        static volatile uint32_t prev_pulse_us_;
        static uint32_t pulse_dt_us_;
        static float freq_hz_;

    private:

        M1SpeedSensor() {};

};


template<int TPin>
void M1SpeedSensor<TPin>::initialize()
{
    curr_pulse_us_ = CurrPulseTimeoutVal_us_;
    prev_pulse_us_ = PrevPulseTimeoutVal_us_;
    pulse_dt_us_ = PulseDtTimeoutVal_us_;
    freq_hz_ = 0.0;

    pinMode(TPin, INPUT);
    attachInterrupt(TPin, update_on_pin, RISING);
}



template<int TPin>
float M1SpeedSensor<TPin>::freq_hz()
{
    return freq_hz_;
}


template<int TPin>
float M1SpeedSensor<TPin>::speed()
{
    return WindSpeedCalibSlope*freq_hz_ + WindSpeedCalibOffset;
}

template<int TPin>
void M1SpeedSensor<TPin>::update_on_loop()
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


template<int TPin>
inline void M1SpeedSensor<TPin>::update_on_pin()
{
    prev_pulse_us_ = curr_pulse_us_;
    curr_pulse_us_ = micros();
}


template<int TPin>
const uint32_t M1SpeedSensor<TPin>::CurrPulseTimeoutVal_us_ = -1*(WindSpeedPulseTimeout + 1);


template<int TPin>
const uint32_t M1SpeedSensor<TPin>::PrevPulseTimeoutVal_us_ = -1*(WindSpeedPulseTimeout + 1);


template<int TPin>
const uint32_t M1SpeedSensor<TPin>::PulseDtTimeoutVal_us_ = WindSpeedPulseTimeout + 1;


template<int TPin>
volatile uint32_t M1SpeedSensor<TPin>::curr_pulse_us_ = CurrPulseTimeoutVal_us_;


template<int TPin>
volatile uint32_t M1SpeedSensor<TPin>::prev_pulse_us_ = PrevPulseTimeoutVal_us_;


template<int TPin>
uint32_t M1SpeedSensor<TPin>::pulse_dt_us_ = PulseDtTimeoutVal_us_;


template<int TPin>
float M1SpeedSensor<TPin>::freq_hz_ = 0.0;


#endif
